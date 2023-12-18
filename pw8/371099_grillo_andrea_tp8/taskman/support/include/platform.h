#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define UART_BASE 0x50000000
#define SWITCHES_BASE 0x50000080

void platform_glinit();

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H_INCLUDED */
