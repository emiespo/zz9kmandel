#include "SDI_compiler.h"

#include <libraries/asl.h>

#include <proto/asl.h>
#include <proto/intuition.h>
#include <intuition/screens.h>
#include <proto/Picasso96.h>

struct Screen* openScreen(const char*);
void closeScreen(struct Screen*);