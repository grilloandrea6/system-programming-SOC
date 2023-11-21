#!/bin/bash

SUPPORT=/home/andrea/uni/systemProgrammingForSOC/virtualPrototype/programms/support


or1k-elf-gcc -Os -nostartfiles -o fractal_flpt $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/or32Print.c $SUPPORT/uart.c -I $SUPPORT ../fractal_flpt.c ../main_flpt.c
convert_or32 fractal_flpt
