#ifndef ZZ9K_BRIDGE_H
#define ZZ9K_BRIDGE_H

#include <stdint.h>
#include <exec/types.h>

#include "zz9000.h"

void armReset(struct MNTZZ9KConfigDev*);
void armRun(struct MNTZZ9KConfigDev*, int, uint32_t*);
struct MNTZZ9KConfigDev* configureZZ9K(uint32_t);
void freeZZ9KResources(struct MNTZZ9KConfigDev*);
BOOL loadProgram(const char*, struct MNTZZ9KConfigDev*);

#endif /* ZZ9K_BRIDGE_H */
