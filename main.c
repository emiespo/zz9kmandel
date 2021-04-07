/*
 * MNT ZZ9000 Amiga Graphics and ARM Coprocessor SDK
 *            "zz9k" Amiga CLI tool for loading and executing
 *            ARM applications
 *
 * Copyright (C) 2019, Lukas F. Hartmann <lukas@mntre.com>
 *                     MNT Research GmbH, Berlin
 *                     https://mntre.com
 *
 * More Info: https://mntre.com/zz9000
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * GNU General Public License v3.0 or later
 *
 * https://spdx.org/licenses/GPL-3.0-or-later.html
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <proto/exec.h>

#include "SDI_compiler.h"
#include "zz9000bridge.h"
#include "p96.h"
#include "intuition.h"
#include "mandel.h"

#include "zz9000.h"

#include "main.h"

#define ASL_LIB_VER 38L     // asl library 38+ supports screen mode requesters 

#ifndef ARM_PROGNAME
#define ARM_PROGNAME="arm.bin" // This is supposed to come from the Makefile
#endif

#define ARM_ARGC 4

/**
 * Globals
 */
static struct Screen* zz9kScreen;
static struct MNTZZ9KConfigDev* zz9kConfig;
struct Library *CyberGfxBase = NULL;

int main() {
  // setup env
  setup();

  // run the zz9k program
  if (zz9kScreen) {
    run();
  }

  // Exit
  cleanup();
  return 0;
}

void run() {

  uint32_t armArgs[ARM_ARGC];

  armArgs[1] = zz9kScreen->Width;
  armArgs[2] = zz9kScreen->Height;
  APTR bitmapAddress = getBitmapRGBFormat(zz9kScreen, &armArgs[3]);

  #if PURE_68K == 1
    armArgs[0] = (uint32_t)bitmapAddress;
    #ifdef DEBUG
      printf("Launching pure 68k version. \n");
    #endif
    mandel(ARM_ARGC, armArgs);
  #else
    // Launch the Arm program
    armArgs[0] = ((ULONG)bitmapAddress) - (uint32_t)zz9kConfig->memory+(uint32_t)ZZ9K_MEM_START;
    armRun(zz9kConfig, ARM_ARGC, armArgs);
  #endif

  // Wait for mouse click.
  while (1) {
    volatile uint8_t* mreg = (volatile uint8_t*)0xbfe001;
    if (!(*mreg&(1<<6))) break;
  }
}

void setup() {

  #if PURE_68K == 0
    if (!(zz9kConfig = configureZZ9K(0x0))) {
      __exit("Error: MNT ZZ9000 not found.\n", 1);
    }
  #endif

	CyberGfxBase = OpenLibrary("cybergraphics.library", 41);
	if (!CyberGfxBase) {
	    __exit("Error: can't open cybergraphics.library v41.\n", 1);	
	}

  // Open screen using a screen requester
  zz9kScreen = openScreen("ZZ9K Screen");

  // Init ZZ9K code
  #if PURE_68K == 0
    if (!loadProgram(ARM_PROGNAME, zz9kConfig)) {
      __exit("Error loading program to the zz9k.\n", 1);
    }
  #endif
}

void cleanup() {
  #if PURE_68K == 0
    freeZZ9KResources(zz9kConfig);
  #endif
  closeScreen(zz9kScreen);
  if (CyberGfxBase) {
		CloseLibrary(CyberGfxBase);
	}
}

void __exit(const char* msg, int status) {
  printf(msg);
  cleanup();
  exit(status);
}
