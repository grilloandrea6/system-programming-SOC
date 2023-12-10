#include <platform.h>

#include <perf.h>
#include <tick.h>
#include <uart.h>
#include <vga.h>

#include <stdio.h>

void platform_glinit() {
    uart_glinit((volatile char*)UART_BASE);
    tick_glinit();
    perf_glinit();
}

void _putchar(char c) {
    uart_putc((volatile char*)UART_BASE, c);
    vga_putc(c);
}

int putchar(int c) {
    _putchar(c);
    return 0;
}

int puts(const char* s) {
    uart_puts((volatile char*)UART_BASE, s);
    uart_putc((volatile char*)UART_BASE, (int)'\n');

    vga_puts(s);
    vga_putc((int)'\n');
    return 0;
}

int getchar(void) {
    return uart_getc((volatile char*)UART_BASE);
}
