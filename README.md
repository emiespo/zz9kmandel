# MNT ZZ9000 ARM SDK EXAMPLE

This is my attempt at making a project structure that allows having a simple "all in one" 68K launcher.<br/>
<br/>
This is entirely based on the latest official SDK: https://source.mntmn.com/MNT/zz9000-sdk.<br/>
Please read the official SDK readme first!

# DISCLAIMER

This must be considered EXPERIMENTAL and BUGGY for now. It might just crash your Amiga, you've been warned!

# KNOWN BUGS

It seems to work most of the times, but sometimes it just won't load or end up crashing the board (one of the ARM core gets stuck).<br/>

# Requirements

The provided Amiga makefile is made to work with Bebbo's Amiga GCC toolchain: https://github.com/bebbo/amiga-gcc.<br/>
The default configuration assumes amiga-gcc is installed in /opt/amiga.<br/>
<br/>
To compile the ARM code, please refer to the ZZ9K SDK above (you need to install the GCC version called arm-none-eabi-gcc).

# Configuration

Most of the variables and configs are preset in the Makefiles, with comments.<br/>
A sample config file is provided for Visual Studio Code.<br/>
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
