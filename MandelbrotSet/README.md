# MandelbrotSet for Commodore 64
## Commodore Basic + C programming language (CC65)


## MandelbrotSet in Basic
c64-mandelbrot.bas
c64-mandelbrot.prg


## MandelbrotSet in C

mandelbrot1.c - Normal Mandelbrot Set 
mandelbrot2.c - Petscii Array Mandelbrot Set
mandelbrot3.c - ZoomOut Mandelbrot Set


### Floating point library is needed to build C scripts with a CC65 compiler.
https://github.com/mrdudz/cc65-floatlib


Download zip file and unpack or use git clone:

git clone https://github.com/mrdudz/cc65-floatlib.git

enter this folder:
cd cc65-floatlib

run:
make runtime.lib


Include two header files in your c code "float.h" and "math.h", they are located in "cc65-floatlib" direcotry

When build, use this command: cl65 mandelbrot1.c runtime.lib -o mandelbrot1.prg

You can place "runtime.lib","float.h" and "math.h" in the same directory as your sciprt or 
you can use paths in build command.
