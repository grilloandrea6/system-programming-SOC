#!/bin/bash

SUPPORT=/home/andrea/uni/systemProgrammingForSOC/virtualPrototype/programms/support

#or1k-elf-gcc -S -O0 -nostartfiles  $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/or32Print.c $SUPPORT/uart.c -I $SUPPORT ../test.c
or1k-elf-gcc  -O0 -nostartfiles -o test $SUPPORT/crt0.S $SUPPORT/exceptionHandlers.c $SUPPORT/vgaPrint.c $SUPPORT/or32Print.c $SUPPORT/uart.c -I $SUPPORT ../test.c
convert_or32 test

