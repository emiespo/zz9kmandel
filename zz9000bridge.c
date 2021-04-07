#include <stdio.h>
#include <unistd.h>
#include <proto/exec.h>
#include <proto/expansion.h>

#include "SDI_compiler.h"

#include "zz9000bridge.h"

typedef enum {false, true} bool;

/**
 * Loads a ZZ9000 program
 * @param zzload          contains program name and title
 * @param zz9kConfigDev   zz9k configuration as returned by configureZZ9K()
 * 
 * @return TRUE if the program was successfully loaded
 *    
 */
BOOL loadProgram(const char* programName, struct MNTZZ9KConfigDev* zz9kConfigDev) {

    #ifdef DEBUG
      printf("Loading '%s' to ARM address 0x%lx (Amiga address 0x%lx)\n", programName, ZZ9K_APP_SPACE + zzload->loadOffset, (uint32_t)dest);
    #endif

    zz9kConfigDev->programLoaded = 0;
    FILE* f = fopen(programName, "rb");
    if (f) {
      fseek(f, 0, SEEK_END);
      unsigned long fsize = ftell(f);
      fseek(f, 0, SEEK_SET);
      size_t bytesRead = fread(zz9kConfigDev->dest, 1, fsize, f);
      fclose(f);
      zz9kConfigDev->programLoaded = (bytesRead == fsize);
    }
    return zz9kConfigDev->programLoaded;
}

/**
 * Resets the 2nd ARM CPU on the ZZ9K
 * @see https://source.mntmn.com/MNT/zz9000-firmware/src/branch/master/ZZ9000_proto.sdk/ZZ9000OS/src/main.c#L1081
 */
void armReset(struct MNTZZ9KConfigDev* zz9kConfigDev) { 
  printf("Resetting ARM core...\n");
  zz9kConfigDev->regs->arm_run_hi = 0;
  zz9kConfigDev->regs->arm_run_lo = 0x100;
}

/**
 * Runs the ARM program
 * 
 */
void armRun(struct MNTZZ9KConfigDev* zz9kConfigDev, int armArgc, uint32_t* armArgs) {

    if (!zz9kConfigDev->programLoaded) {
      printf("ERROR: ARM program not loaded yet.\n");
      return;
    }
   
    volatile MNTZZ9KRegs* regs = zz9kConfigDev->regs;

    // pass ARM app arguments
    for (unsigned short i = 0; i < armArgc && i < sizeof(regs->arm_arg) / sizeof(u16); i++) {
      #ifdef DEBUG
        printf("ARM arg%d: %lu (%lx)\n", i, armArgs[i], armArgs[i]);
      #endif
      
      regs->arm_arg[i*2]   = armArgs[i] >> 16;
      regs->arm_arg[i*2+1] = armArgs[i] & 0xffff;
    }
    regs->arm_argc   = armArgc;

    // set ARM run addresses (runs the program!)
    printf("Loading ARM program...\n");
    regs->arm_run_hi = (ZZ9K_APP_SPACE + zz9kConfigDev->loadOffset) >> 16;
    regs->arm_run_lo = (ZZ9K_APP_SPACE + zz9kConfigDev->loadOffset) & 0xffff;
}

struct MNTZZ9KConfigDev* configureZZ9K(uint32_t loadOffset) {
  // Find a ZZ9K
  struct ConfigDev* configDev = NULL; // NULL is a valid param for FindConfigDev.

  configDev = (struct ConfigDev*)FindConfigDev(configDev,0x6d6e,0x4);
  if (!configDev) {
    configDev = (struct ConfigDev*)FindConfigDev(configDev,0x6d6e,0x3);
  }
  struct MNTZZ9KConfigDev* zz9KConfigDev = NULL;
  if (configDev) {
    zz9KConfigDev = AllocVec(sizeof(struct MNTZZ9KConfigDev), MEMF_CLEAR);
    if (!zz9KConfigDev) {
      return NULL;
    }
    zz9KConfigDev->loadOffset = loadOffset;
    zz9KConfigDev->regs = (volatile MNTZZ9KRegs*)(configDev->cd_BoardAddr);
    zz9KConfigDev->memory = (uint8_t*)(configDev->cd_BoardAddr)+0x10000;
    zz9KConfigDev->dest = zz9KConfigDev->memory + ZZ9K_APP_SPACE - ZZ9K_MEM_START + loadOffset;
  }

  return zz9KConfigDev;
}

/**
 * Resets the ARM cpu and frees memory
 * @param       zz9kConfig    config struct that will be freed.
 */
void freeZZ9KResources(struct MNTZZ9KConfigDev* zz9kConfig) {
  if (zz9kConfig) {
    armReset(zz9kConfig);
    FreeVec(zz9kConfig);
  }
}