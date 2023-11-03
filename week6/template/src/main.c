#include <main.h>
#include <perf.h>
#include <swap.h>
#include <exception.h>


void allignment_exception_handler() {
    puts("MYYallig!");
}

void system_call_handler() {
    uint32_t epc = SPR_READ(SPR_EPC);
    printf("SYSTEM_CALL : \t 0x%08x\n",epc);


    uint32_t instr1,instr2;
    asm volatile("l.lwz %[d], 0(%[s])" : [d]"=r"(instr1) : [s]"r"(epc));

    epc -= 4;
    asm volatile("l.lwz %[d], 0(%[s])" : [d]"=r"(instr2) : [s]"r"(epc));

    printf("INSTRUCTION at EPC : \t 0x%08x\n",instr1);
    printf("INSTRUCTION at EPC-4 : \t 0x%08x\n",instr2);
}


int main() {
    // initializes the UART, performance counters, peripherals etc.
    platform_init();

    printf("Hello, world from %s (%s:%2d)!\n", __func__, __FILE__, __LINE__);

/*
int *addr = (int *) 0xFFFFFFFFF00; // choose whatever address you want
int data;
asm volatile("l.lwz %[d], 0(%[s])" : [d]"=r"(data) : [s]"r"(addr));
*/

SYSCALL(0xAF);




/*    printf("no swap: 0x%04x, swap_u16: 0x%04x\n", 0xDEAD, swap_u16(0xDEAD));
    printf("no swap: 0x%08x, swap_u32: 0x%08x\n", 0xDEADBEEF, swap_u32(0xDEADBEEF));
*/
/*    perf_start()
    while (1) {
        perf_print_time(PERF_COUNTER_RUNTIME, "runtime");
        perf_print_cycles(PERF_COUNTER_RUNTIME, "runtime");
        for (volatile int i = 0; i < 1000000; ++i) ;
    }
    perf_stop();
*/
    return 0;
}
