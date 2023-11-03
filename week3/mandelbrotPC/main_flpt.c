#include "fractal_flpt.h"
#include <stdio.h>

// Constants describing the output device
const int SCREEN_WIDTH = 512;   //!< screen width
const int SCREEN_HEIGHT = 512;  //!< screen height

extern float maximum;


// Constants describing the initial view port on the fractal function
const float FRAC_WIDTH = 3.0; //!< default fractal width 
const float CX_0 = -2.0;      //!< default start x-coordinate 
const float CY_0 = -1.5;      //!< default start y-coordinate 
const uint16_t N_MAX = 640;    //!< maximum number of iterations

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
   rgb565 frameBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

   float delta = FRAC_WIDTH / SCREEN_WIDTH;
   int i;
   
   printf(" starting calculation\n\n");
   for (i = 0 ; i < SCREEN_WIDTH*SCREEN_HEIGHT ; i++) frameBuffer[i]=0;

   draw_fractal(frameBuffer,SCREEN_WIDTH,SCREEN_HEIGHT,&calc_mandelbrot_point_soft, &iter_to_colour,CX_0,CY_0,delta,N_MAX);
   
   printf("%f finished\n\n",maximum);
}
