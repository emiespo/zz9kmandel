CC=arm-none-eabi-gcc
COMPILE=$(CC) -std=gnu99 -nostdlib -O2 -c -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -I./lib
LINK=$(CC) -T ./link.ld -std=gnu99 -nostdlib -O2 -mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard
ODIR=build-arm

# Sets program name variables, eg:
# mandel-arm.bin -> mandel-arm
# mandel
ARM_PROGNAME_NOBIN=$(subst .bin,,$(ARM_PROGNAME))
PROGNAME=$(subst -arm,,$(ARM_PROGNAME_NOBIN))

INCLUDE=$(ARM_INCLUDES)

all: setup compile link

setup:
	cppcheck --template='{file}:{line}:{severity}:{message}' --enable=all -I./lib main.c
	mkdir -p $(ODIR)

compile:
	# Compiling mandel.c from parent folder. this is shared with the 68k program, for benchmarks :)
	$(COMPILE) $(INCLUDE) -DZZ9K_ARM_CODE='1' -DPURE_68K=0 -o $(ODIR)/$(PROGNAME).o ../$(PROGNAME).c
	$(COMPILE) -I. -ftree-vectorize -o $(ODIR)/main.o main.c
	$(COMPILE) -o $(ODIR)/idiv.o ./lib/div/idiv.S
	$(COMPILE) -o $(ODIR)/idivmod.o ./lib/div/idivmod.S
	$(COMPILE) -o $(ODIR)/ldivmod.o ./lib/div/ldivmod.S
	$(COMPILE) -o $(ODIR)/memset.o ./lib/memory/memset.c
	$(COMPILE) -o $(ODIR)/memcpy.o ./lib/memory/memcpy.c
	$(COMPILE) -o $(ODIR)/printf.o ./lib/printf/printf.c

link:
	$(LINK) -o $(ODIR)/$(ARM_PROGNAME_NOBIN) $(ODIR)/main.o $(ODIR)/$(PROGNAME).o $(ODIR)/memcpy.o $(ODIR)/memset.o $(ODIR)/printf.o $(ODIR)/*div*.o -L. -lm
	arm-none-eabi-objcopy -O binary $(ODIR)/$(ARM_PROGNAME_NOBIN) $(ODIR)/$(ARM_PROGNAME)

clean:
	rm -rf ./$(ODIR)/*

# In my setup, this folder is shared with the Amiga, so it can be copied easily
copy:
	cp $(ODIR)/$(ARM_PROGNAME) ~/Downloads