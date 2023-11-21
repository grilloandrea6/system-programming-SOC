#ifndef FRACTAL_FLPT_H
#define FRACTAL_FLPT_H

#include <stdint-gcc.h>

//! macro to convert a standard int or float to my_fixed format
#define convertToMyFixed(src) ((int32_t)(src * 16777216.0))

//! macro to multiply two my_fixed numbers
#define multiplyFixed(x,y) (my_fixed)(((int64_t)x * (int64_t)y)>>24)

//! my_fixed typedef definition
typedef uint32_t my_fixed;

//! Colour type (5-bit red, 6-bit green, 5-bit blue)
typedef uint16_t rgb565;

//! \brief Pointer to fractal point calculation function
typedef uint16_t (*calc_frac_point_p)(my_fixed cx, my_fixed cy, uint16_t n_max);

uint16_t calc_mandelbrot_point_soft(my_fixed cx, my_fixed cy, uint16_t n_max);

//! Pointer to function mapping iteration to colour value
typedef rgb565 (*iter_to_colour_p)(uint16_t iter, uint16_t n_max);

rgb565 iter_to_bw(uint16_t iter, uint16_t n_max);
rgb565 iter_to_grayscale(uint16_t iter, uint16_t n_max);
rgb565 iter_to_colour(uint16_t iter, uint16_t n_max);

void draw_fractal(rgb565 *fbuf, int width, int height,
                  calc_frac_point_p cfp_p, iter_to_colour_p i2c_p,
                  my_fixed cx_0, my_fixed cy_0, my_fixed delta, uint16_t n_max);

#endif // FRACTAL_FLPT_H
