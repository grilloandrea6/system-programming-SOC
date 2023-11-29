#include <stdio.h>
#include <stddef.h>
#include <cache.h>
#include <perf.h>
#include <vga.h>
#include <dma.h>
#include <swap.h>
#include <defs.h>
#include "fractal_fxpt.h"

//#define __REALLY_FAST__

int main() {
   volatile unsigned int *vga = (unsigned int *) 0X50000020;
   volatile unsigned int reg, hi;
   uint32_t *pixel;
   
   rgb565 *frameBuffer = (rgb565 *) 0x10000;

   perf_init();
   perf_set_mask(PERF_COUNTER_0, PERF_ICACHE_NOP_INSERTION_MASK | PERF_STALL_CYCLES_MASK);
   perf_set_mask(PERF_COUNTER_1, PERF_BUS_IDLE_MASK);
   perf_set_mask(PERF_COUNTER_2, PERF_ICACHE_MISS_MASK);
   perf_set_mask(PERF_COUNTER_3, PERF_DCACHE_MISS_MASK);

   vga_clear();
   printf("Starting drawing a fractal\n");
   fxpt_4_28 delta = FRAC_WIDTH / SCREEN_WIDTH;

   /* enable the caches */
   icache_write_cfg( CACHE_FOUR_WAY | CACHE_SIZE_8K | CACHE_REPLACE_LRU );
   dcache_write_cfg( CACHE_DIRECT_MAPPED | CACHE_SIZE_8K | CACHE_WRITE_BACK);
   icache_enable(1);

   /* Enable the vga-controller's graphic mode */
   vga[0] = swap_u32(SCREEN_WIDTH);
   vga[1] = swap_u32(SCREEN_HEIGHT);
   vga[3] = swap_u32( (unsigned int) &frameBuffer[0] );
   
   /* Clear screen */
   for (int i = 0 ; i < SCREEN_WIDTH*SCREEN_HEIGHT ; i++) frameBuffer[i]=0;
   
   /* enable the data cache */
   dcache_enable(1);

   perf_start();
#ifdef __REALLY_FAST__
   // DEFINITION OF POINTERS FOR SPM AND DMA
   uint32_t *bufferStart = (uint32_t *) 0xC0000000;
   size_t bufferSize = 256;
   volatile uint32_t *dma = (uint32_t *) DMA_BASE_ADDRESS; 


   int color = (2<<16) | N_MAX;
   asm volatile ("l.nios_crc r0,%[in1],%[in2],0x21"::[in1]"r"(color),[in2]"r"(delta));
   //pixel = (uint32_t *)frameBuffer;
   fxpt_4_28 cy = CY_0;
   for (int k = 0 ; k < SCREEN_HEIGHT ; k++) { // foreach line
    
    // start writing the line at the bufferStart
    pixel = bufferStart;     


     fxpt_4_28 cx = CX_0;
     for (int i = 0 ; i < SCREEN_WIDTH ; i+=2) {
       asm volatile ("l.nios_rrr %[out1],%[in1],%[in2],0x20":[out1]"=r"(color):[in1]"r"(cx),[in2]"r"(cy));
       *(pixel++) = color;
       cx += delta << 1;
     }
    
     // now set the DMA

     
     dma[MEMORY_ADDRESS_ID] = swap_u32((uint32_t *)(frameBuffer) + k*256);
     dma[SPM_ADDRESS_ID] = swap_u32(bufferStart);
     dma[TRANSFER_SIZE_ID] = swap_u32(bufferSize);
     dma[START_STATUS_ID] = swap_u32(63);

     //printf("STARTING DMA\n");
     dma[START_STATUS_ID] = swap_u32(DMA_FROM_SPM_TO_MEM);

     while (swap_u32(dma[START_STATUS_ID]) & 0x1);//printf(".");
     printf("DMA has finished, going forward");
     cy += delta;
   }



#else
   draw_fractal(frameBuffer,SCREEN_WIDTH,SCREEN_HEIGHT,&calc_mandelbrot_point_soft, &iter_to_colour,CX_0,CY_0,delta,N_MAX);
#endif
   dcache_flush();
   asm volatile ("l.lwz %[out1],0(%[in1])":[out1]"=r"(pixel):[in1]"r"(frameBuffer)); // dummy instruction to wait until the cache is flushed.
   perf_stop();

   printf("Done\n");
   perf_print_cycles( PERF_COUNTER_2 , "I$ misses" );
   perf_print_cycles( PERF_COUNTER_3 , "D$ misses" );
   perf_print_cycles( PERF_COUNTER_0 , "Stall time" );
   perf_print_cycles( PERF_COUNTER_1 , "Bus idle time" );
   perf_print_cycles( PERF_COUNTER_RUNTIME , "Runtime" );
}
