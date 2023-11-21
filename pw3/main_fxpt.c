#include "fractal_fxpt.h"
/*#include "../support/or32Print.h"
#include "../support/vgaPrint.h"
#include "../support/profiling.h"
#include "../support/uart.h"
#include "../support/caches.h"
*/
#include <or32Print.h>
#include <vgaPrint.h>
#include <profiling.h>
#include <uart.h>
#include <caches.h>
#include <stddef.h>

#define swapBytes( source , dest ) asm volatile ("l.nios_rrc %[out1],%[in1],r0,0x1":[out1]"=r"(dest):[in1]"r"(source));

// Constants describing the output device
const int SCREEN_WIDTH = 128;//512;   //!< screen width
const int SCREEN_HEIGHT = 128;//512;  //!< screen height

// Constants describing the initial view port on the fractal function
const fxpt_4_28 FRAC_WIDTH = 0x30000000; //!< default fractal width (3.0 in Q4.28)
const fxpt_4_28 CX_0 = 0xe0000000;       //!< default start x-coordinate (-2.0 in Q4.28)
const fxpt_4_28 CY_0 = 0xe8000000;       //!< default start y-coordinate (-1.5 in Q4.28)
const rgb565 N_MAX = 64;                 //!< maximum number of iterations

void *memset (void *dest, int val, size_t len) {
  switch (__builtin_object_size(dest,0)) {
    case 1  : short *ptr1 = dest;
              while (len-- > 0) *(ptr1++) = val;
              return dest;
    case 2  : int *ptr2 = dest;
              while (len-- > 0) *(ptr2++) = val;
              return dest;
    default : char *ptr3 = dest;
              while (len-- > 0) *(ptr3++) = val;
              return dest;
  }
}

int main() {
   volatile unsigned int *vga = (unsigned int *) 0X50000020;
   volatile unsigned int reg, hi;
   rgb565 frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
   setMemoryDistance(25);
   vgaClear();


   setProfilingCounterMask(PROFILING_COUNTER_0, STALL_CYCLES_MASK | I_CACHE_NOP_INSERTION_MASK);
   setProfilingCounterMask(PROFILING_COUNTER_1, BUS_IDLE_MASK);
   setProfilingCounterMask(PROFILING_COUNTER_2, I_CACHE_MISS_MASK | 0x0);



   or32Print(&vgaPrintChar, "Starting drawing a fractal\n");
   fxpt_4_28 delta = FRAC_WIDTH / SCREEN_WIDTH;
   int i;
   /* enable the caches */

   setInstructionCacheConfig( CACHE_DIRECT_MAPPED | CACHE_SIZE_8k | CACHE_REPLACE_FIFO );
   enableInstructionCache(reg);


   /* Enable the vga-controller's graphic mode */
   swapBytes( SCREEN_WIDTH, vga[0]);
   swapBytes( SCREEN_HEIGHT, vga[1]);
   swapBytes((unsigned int)&frameBuffer[0], vga[3]);

   /* Clear screen */
   for (i = 0 ; i < SCREEN_WIDTH*SCREEN_HEIGHT ; i++) frameBuffer[i]=0;

   startProfiling();
   draw_fractal(frameBuffer,SCREEN_WIDTH,SCREEN_HEIGHT,&calc_mandelbrot_point_soft, &iter_to_colour,CX_0,CY_0,delta,N_MAX);
   stopProfiling();


   or32Print(&vgaPrintChar, "Done\n");
   or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "Fixed point ");
   printCacheConfig();

   printProfilingTime( PROFILING_COUNTER_0 , "Stall cycles    " );
   printProfilingTime( PROFILING_COUNTER_1 , "Bus idle cycles " );
   printProfilingTime( RUN_TIME_COUNTER , "Runtime cycles  " );
   printProfilingTime( PROFILING_COUNTER_2 , "Instruction Cache Miss cycles " );

}
