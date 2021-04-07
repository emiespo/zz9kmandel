#
# Based on Bebbo's GCC toolchain.
# https://github.com/bebbo/amiga-gcc
#

# You can configure the names of the main executable here.
PROGNAME = mandel
68K_PROGNAME = $(PROGNAME)-68k
# To change this one, also change substititions arm-code/Makefile
ARM_PROGNAME = '$(PROGNAME)-arm.bin'
# Any extra include that might be needed from the ARM side to use includes from the Amiga side.
ARM_INCLUDES= # use the format: "-I..."

# Set this to 1 to build a pure 68k exe (benchmarks, etc.). This is also needed to fix endianess.
# Make sure to run "make clean" if you change this.
PURE_68K=0

# Exported to the ARM side
export ARM_PROGNAME
export ARM_INCLUDES
export PURE_68K

# Subfolder containing the arm code and makefile
ARM_FOLDER=arm-code
# Change accordingly. Setting a 68060 with GCC math libraries makes a *huge* difference in speed.
CPU=68020

AMIGA_GCC_ROOT=/opt/amiga
AMIGA_GCC_BIN=$(AMIGA_GCC_ROOT)/bin
CC=$(AMIGA_GCC_BIN)/m68k-amigaos-gcc
WARN     = -W -Wall -Wwrite-strings -Wpointer-arith -Wsign-compare -Wno-pointer-sign #-Wunreachable-code
CFLAGS	 = $(WARN) -mcrt=clib2 $(INCLUDE) -fbaserel -m$(CPU) -Os -fomit-frame-pointer -DMULTIBASE -DBASEREL -D__amigaos3__
CFLAGS   += -DARM_PROGNAME=\"$(ARM_PROGNAME)\" -DPURE_68K=$(PURE_68K)
ODIR=build-68k

_OBJS = intuition.o zz9000bridge.o p96.o main.o
ifeq ($(PURE_68K), 1)
_OBJS += $(PROGNAME).o
endif

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

LDFLAGS	= -noixemul -fbaserel -lm -pg

all: setup make_arm $(68K_PROGNAME) copy

setup:
	mkdir -p $(ODIR)

make_arm:
ifeq ($(PURE_68K), 0)
	$(MAKE) -C $(ARM_FOLDER)
endif

$(68K_PROGNAME) : $(OBJS) 
	$(CC) $(OBJS) $(LDFLAGS) -g -o $(ODIR)/$(68K_PROGNAME)

$(ODIR)/%.o : %.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f $(ODIR)/*
	$(MAKE) -C $(ARM_FOLDER) clean

# In my setup, this folder is shared with the Amiga, so it can be copied easily
copy:
	cp $(ODIR)/$(68K_PROGNAME) ~/Downloads
ifeq ($(PURE_68K), 0)
	$(MAKE) -C $(ARM_FOLDER) copy
endif
