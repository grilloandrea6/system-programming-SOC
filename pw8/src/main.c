#include <cache.h>
#include <coro/coro.h>
#include <defs.h>
#include <platform.h>
#include <stdio.h>
#include <taskman/taskman.h>
#include <taskman/tick.h>
#include <taskman/uart.h>

void part1();
void part2();

int main() {
    platform_glinit();

    icache_write_cfg(CACHE_DIRECT_MAPPED | CACHE_SIZE_8K);
    dcache_write_cfg(CACHE_DIRECT_MAPPED | CACHE_SIZE_8K | CACHE_WRITE_BACK);
    icache_enable(1);
    dcache_enable(1);

    coro_glinit();
    taskman_glinit();
    taskman_tick_glinit();
    taskman_uart_glinit();

    part1();
    part2();

    return 0;
}
