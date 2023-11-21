#!/bin/bash
SUPPORT=/home/andrea/Dropbox/EPFL/systemProgrammingForSOC/virtualPrototype/programms/support

or1k-elf-gcc -Os -nostartfiles -o fractal_fxpt $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/uart.c $SUPPORT/or32Print.c $SUPPORT/caches.c $SUPPORT/profiling.c -I $SUPPORT ../fractal_fxpt.c ../main_fxpt.c
convert_or32 fractal_fxpt
