# MNT ZZ9000 ARM SDK EXAMPLE (MANDELBROT SET)

This is my attempt at making a project structure that allows having a simple "all in one" 68K launcher.<br/>
<br/>
The idea is mostly educational around the ZZ9K and mixed makefiles/compilers/architecture.<br/>
The main program is in `mandel.c` and simply draws a Mandelbrot set.</br>
With the default configuration, this code is compiled into an ARM executable that can run on the ZZ9K SDK.<br/>
It can also be compiled into a pure 68K executable (for benchmark/performance evaluation) configuring the Makefile
</br>
Please also read the official SDK documentation: https://source.mntmn.com/MNT/zz9000-sdk.<br/>

# DISCLAIMER

This must be considered EXPERIMENTAL and BUGGY for now. It might just crash your Amiga, you've been warned!

# KNOWN BUGS

It seems to work most of the times, but sometimes it just won't load or end up crashing the board (one of the ARM core gets stuck).<br/>
Apparently this is due to the second ARM core not properly resetting and getting stuck somewhere (an IRQ?).<br/>
Seems to be an issue with firmwares 1.5+ (at least on my setup even the existing examples have never worked properly).

# Requirements

The provided Amiga makefile is made to work with Bebbo's Amiga GCC toolchain: https://github.com/bebbo/amiga-gcc.<br/>
The default configuration assumes amiga-gcc is installed in /opt/amiga.<br/>
<br/>
To compile the ARM code, please refer to the ZZ9K SDK above (you need to install the GCC version called arm-none-eabi-gcc).<br/>


# Configuration

Most of the variables and configs are preset in the Makefiles, with comments.<br/>
A sample config file is provided for Visual Studio Code.<br/
It also assumes that Bebbo's amiga-gcc is installed in /opt/amiga/ (see above).<br/>

# Building

Provided you have a working Bebbo's installation, you can simply run<br/>

```
make
```

from the project root.<br/>
This would create the two executables:<br/>

```
build/mandel-68k        ; 68000 executable
build/mandel-arm.bin    ; ARM executable
```

copy them on the same folder in your Amiga and you should be good to go!<br/>

# Debugging

The VSCode configuration allows remote debugging (yes, it kinda works!) thanks again to Bebbo's efforts: https://github.com/bebbo/bgdbserver
You should launch the bgdbserver on the Amiga (see documentation) and then point at it via the `miDebuggerServerAddress` param in the `(gdb) Remote Attach` configuration provided.<br/>

Have fun!
