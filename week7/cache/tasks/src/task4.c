#include <cache.h>
#include <swap.h>
#include <stdio.h>
#include <task4.h>

/*
 * AG macros to define which solution to use
 * 1 - just disable the cache
 * 2 - use a write-through cache
 * 3 - use LEDS_OLD_BASE address
 * 4 - use dcache_flush at the end of each iteration
 */
#define SOL_NUMBER 4

// YOU ARE NOT SUPPOSED TO MODIFY ANY OF THE FOLLOWING MACROS.

// old base address
#define LEDS_OLD_BASE 0x50000800ull

// new base address
#define LEDS_NEW_BASE 0x08000800ull

// pixel-based control of LEDs
#define LEDS_LEDS_OFFSET 0x400ull

// the base address is configurable.
// defines the offset of the base address register.
#define LEDS_BASEADDR_OFFSET 0x7FCull

void init_dcache() {
    // YOU CAN MODIFY THIS.
    dcache_enable(0);

#if SOL_NUMBER == 2
    dcache_write_cfg(CACHE_FOUR_WAY | CACHE_SIZE_4K | CACHE_REPLACE_LRU | CACHE_WRITE_THROUGH);
    dcache_enable(1);
#elif SOL_NUMBER != 1
    dcache_write_cfg(CACHE_FOUR_WAY | CACHE_SIZE_4K | CACHE_REPLACE_LRU | CACHE_WRITE_BACK);
    dcache_enable(1);
#endif
}

/**
 * @brief This functions moves the base address of the LED controller to LEDS_NEW_BASE.
 * 
 */
void init_leds() {
    // note the endianness difference
    volatile uint32_t* baseaddr = (volatile uint32_t*)(LEDS_OLD_BASE + LEDS_BASEADDR_OFFSET);
    printf("original address: 0x%p\n", swap_u32(*baseaddr));
    
    *baseaddr = swap_u32(LEDS_NEW_BASE);

    baseaddr = (volatile uint32_t*)(LEDS_NEW_BASE + LEDS_BASEADDR_OFFSET);
    printf("new address: 0x%p\n", swap_u32(*baseaddr));
}

void bouncing_ball() {
    // YOU CAN MODIFY THIS.
    int xdir, ydir, xpos, ypos, index;
#if SOL_NUMBER != 3
    volatile unsigned int* leds = (unsigned int*)(LEDS_NEW_BASE + LEDS_LEDS_OFFSET);
#else
    volatile unsigned int* leds = (unsigned int*)(LEDS_OLD_BASE + LEDS_LEDS_OFFSET);
#endif
    xdir = ydir = 1;
    xpos = ypos = 5;
    while (1) {
        index = ypos * 12 + xpos;
        leds[index] = 0;
        if (ypos == 8)
            ydir = -1;
        if (ypos == 0)
            ydir = 1;
        if (xpos == 11)
            xdir = -1;
        if (xpos == 0)
            xdir = 1;
        ypos += ydir;
        xpos += xdir;
        index = ypos * 12 + xpos;
        leds[index] = swap_u32(2);
#if SOL_NUMBER == 4
        dcache_flush();
#endif
        for (volatile long i = 0; i < 100000; i++)
            ;
    }
}

void task4_main() {
    puts(__func__);
    init_dcache();
#if SOL_NUMBER != 3
    init_leds();
#endif
    bouncing_ball();
}
