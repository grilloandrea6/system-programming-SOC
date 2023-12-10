#include <coro/coro.h>
#include <defs.h>
#include <stdio.h>
#include <taskman/taskman.h>
#include <taskman/tick.h>
#include <taskman/uart.h>

static void wait_task() {
    uint32_t arg = (uint32_t)coro_arg();
    uint32_t t0 = taskman_tick_now();

    while (1) {
        taskman_tick_wait_for(arg);
        printf("%s: now = %u ms (period = %u)\n", __func__, taskman_tick_now() - t0, arg);
    }

    coro_return(NULL);
}

static void uart_task() {
    uint8_t buf[4096 /* vary this, maybe. */];
    int total_len = 0;

    while (1) {
        int len = taskman_uart_getline(buf, sizeof(buf));
        total_len += len;
        printf(
            "UART received line with length = %d (total = %d): %s\n",
            len, total_len, buf
        );
    }

    coro_return(NULL);
}

void part2() {
    printf("now executing: %s\n", __func__);

    taskman_spawn(&wait_task, (void*)1000, 1024);
    taskman_spawn(&wait_task, (void*)3000, 1024);
    taskman_spawn(&wait_task, (void*)9000, 1024);
    taskman_spawn(&uart_task, NULL, 5120);

    taskman_loop();
}
