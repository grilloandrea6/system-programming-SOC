#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*exception_handler_t)(void);

enum {
    EXCEPTION_RESET,
    EXCEPTION_BUS_ERROR,
    EXCEPTION_DATA_PAGE_FAULT,
    EXCEPTION_INSTRUCTION_PAGE_FAULT,
    EXCEPTION_TICK_TIMER,
    EXCEPTION_ALLIGNMENT_EXCEPTION,
    EXCEPTION_ILLEGAL_INSTRUCTION,
    EXCEPTION_EXTERNAL_INTERRUPT,
    EXCEPTION_DTLB_MISS,
    EXCEPTION_ITLB_MISS,
    EXCEPTION_RANGE_EXCEPTION,
    EXCEPTION_SYSTEM_CALL,
    EXCEPTION_BREAK_POINT,
    EXCEPTION_TRAP,
    EXCEPTION_COUNT
};

extern exception_handler_t _vectors[EXCEPTION_COUNT];

#define SYSCALL(n) \
    asm volatile("l.sys " #n::)

#ifdef __cplusplus
}
#endif

#endif /* EXCEPTION_H_INCLUDED */
