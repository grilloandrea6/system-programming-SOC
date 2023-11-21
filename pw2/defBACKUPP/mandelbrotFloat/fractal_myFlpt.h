#ifndef FRACTAL_FLPT_H
#define FRACTAL_FLPT_H

#include <stdint-gcc.h>


// - - - ADDED CODE BEGIN - - 

/*
 * useful macros during debugging to convert values  
 * #define floatToMyFloat(a) (*(uint32_t *)(&(a)))
 * #define myFloatToFloat(a) (*(float *)(&(a))) 
 */

//! modifies the first bit to change sign of a number 
#define changeSign(a) ((a)^(0x80000000))

//! multiplies by two by summing 1 to the exponent of a number 
#define multiplyByTwo(a) ((a)+(0x800000))

//! constant for value 4.0 
#define MYFLOAT_FOUR 0x40800000

//! definition of myFloat typedef, 32bit unsigned integer 
typedef uint32_t myFloat;

//! \brief  Sum two myFloat values
myFloat sumMyFloat(myFloat a, myFloat b);

//! \brief  Multiply two myFloat values
myFloat multMyFloat(myFloat a, myFloat b);

//! \brief  Check if a myFloat value is less than another one
uint8_t lessThan(myFloat a, myFloat b);

// - - - ADDED CODE END - - 

//! Colour type (5-bit red, 6-bit green, 5-bit blue)
typedef uint16_t rgb565;

//! \brief Pointer to fractal point calculation function
typedef uint16_t (*calc_frac_point_p)(myFloat cx, myFloat cy, uint16_t n_max);

uint16_t calc_mandelbrot_point_soft(myFloat cx, myFloat cy, uint16_t n_max);

//! Pointer to function mapping iteration to colour value
typedef rgb565 (*iter_to_colour_p)(uint16_t iter, uint16_t n_max);

rgb565 iter_to_bw(uint16_t iter, uint16_t n_max);
rgb565 iter_to_grayscale(uint16_t iter, uint16_t n_max);
rgb565 iter_to_colour(uint16_t iter, uint16_t n_max);

void draw_fractal(rgb565 *fbuf, int width, int height,
                  calc_frac_point_p cfp_p, iter_to_colour_p i2c_p,
                  myFloat cx_0, myFloat cy_0, myFloat delta, uint16_t n_max);

#endif // FRACTAL_FLPT_H
