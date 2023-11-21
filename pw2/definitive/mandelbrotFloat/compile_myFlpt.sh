#!/bin/bash

# to be modified to link to the support directory
SUPPORT=/home/andrea/uni/systemProgrammingForSOC/virtualPrototype/programms/support

or1k-elf-gcc -Os -nostartfiles -o fractal_myFlpt $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/or32Print.c -I $SUPPORT ../fractal_myFlpt.c ../myFloat.c ../main_myFlpt.c 
convert_or32 fractal_myFlpt
