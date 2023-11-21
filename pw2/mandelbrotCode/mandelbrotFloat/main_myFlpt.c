#include "myFloat.h"
#include "fractal_myFlpt.h"
#include <or32Print.h>
#include <vgaPrint.h>
#include <stddef.h>

#define swapBytes( source , dest ) asm volatile ("l.nios_rrc %[out1],%[in1],r0,0x1":[out1]"=r"(dest):[in1]"r"(source));

// Constants describing the output device
const int SCREEN_WIDTH = 512;   //!< screen width
const int SCREEN_HEIGHT = 512;  //!< screen height

// Constants describing the initial view port on the fractal function
const myFloat FRAC_WIDTH = 0x40400000; //!< default fractal width 
const myFloat CX_0 = 0xc0000000;       //!< default start x-coordinate
const myFloat CY_0 = 0xbfc00000;       //!< default start y-coordinate
const uint16_t N_MAX = 64;             //!< maximum number of iterations

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
   volatile unsigned int *vga = (unsigned int *) 0x50000020;
   volatile unsigned int reg;
   rgb565 frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

   /* delta = FRAC_WIDTH / SCREEN_WIDTH;  division not implemented */
   myFloat delta = 0x3bc00000;

   int i;
   vgaClear();
   or32Print(&vgaPrintChar, "Starting drawing a fractal usign a custom implementation of floating point calculations\n");
   /* enable the instruction cache */
   asm volatile ("l.mfspr %[out1],r0,17":[out1]"=r"(reg));
   reg |= 1<<4;
   asm volatile ("l.mtspr r0,%[in1],17"::[in1]"r"(reg));
   /* Enable the vga-controller's graphic mode */
   swapBytes(SCREEN_WIDTH, vga[0]);
   swapBytes(SCREEN_HEIGHT, vga[1]);
   swapBytes((unsigned int)&frameBuffer[0], vga[3]);
   /* Clear screen */
   for (i = 0 ; i < SCREEN_WIDTH*SCREEN_HEIGHT ; i++) frameBuffer[i]=0;

   draw_fractal(frameBuffer,SCREEN_WIDTH,SCREEN_HEIGHT,&calc_mandelbrot_point_soft, &iter_to_colour,CX_0,CY_0,delta,N_MAX);
   or32Print(&vgaPrintChar, "Done\n");

   /* flush the datacache */
   asm volatile ("l.mtspr r0,%[in1],5"::[in1]"r"(1<<29));
}
