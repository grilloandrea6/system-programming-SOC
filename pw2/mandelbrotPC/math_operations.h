#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

typedef struct my_number* my_number_t;

my_number_t create_from_float(float a);
my_number_t create_from_int(int a);

my_number_t sum(my_number_t a, my_number_t b);
my_number_t multiply(my_number_t a, my_number_t b);

#endif
