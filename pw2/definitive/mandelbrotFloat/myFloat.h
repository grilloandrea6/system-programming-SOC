#ifndef MYFLOAT_H

#include <stdint-gcc.h>

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

#endif
