#include <stdio.h>
#include <defs.h>

__weak void bus_error_handler() {
    puts("bus error!");
}

__weak void data_page_fault_handler() {
    puts("Data page fault");
}

__weak void instruction_page_fault_handler() {
    puts("i page fault");
}

__weak void tick_timer_handler() {
    puts("tick");
}

__weak void allignment_exception_handler() {
    puts("allig!");
}

__weak void illegal_instruction_handler() {
    puts("???? ");
}

__weak void external_interrupt_handler() {
    puts("ping");
}

__weak void dtlb_miss_handler() {
    puts("dtlb");
}

__weak void itlb_miss_handler() {
    puts("itlb");
}

__weak void range_exception_handler() {
    puts("Range!");
}

__weak void system_call_handler() {
    puts("Syscall");
}

__weak void trap_handler() {
    puts("Trap!");
}

__weak void break_point_handler() {
    puts("Break");
}
