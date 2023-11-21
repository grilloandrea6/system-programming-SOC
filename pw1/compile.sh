#!/bin/bash

SUPPORT=/home/andrea/systemProgrammingForSOC/virtualPrototype/programms/support

or1k-elf-gcc -O2 -nostartfiles -o base20 $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/or32Print.c $SUPPORT/uart.c -I $SUPPORT ../base20.c
convert_or32 base20

