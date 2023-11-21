#include "myFloat.h"


//! \brief  Sum two myFloat values
//! \param  a  first operand
//! \param  b  second operand
//! \return       sum
myFloat sumMyFloat(myFloat a, myFloat b) {
  /* calculation of the exponents, a exponent will be the same as the result */
  uint32_t expRes = (a & 0x7F800000);
  uint32_t expB = (b & 0x7F800000);

  /* 
   * we want the bigger exponent to be in expRes to ease shifts
   * just run again the function recursively if not the case
   */
  if (expRes < expB)
    return sumMyFloat(b,a);

  /* extract mantissas: mask to extract the 23 LSBs and add 1 in the 24th bit */
  int32_t manA = (int32_t)((a & 0x7FFFFF) | 0x800000);
  int32_t manB = (int32_t)((b & 0x7FFFFF) | 0x800000);

  /* shift the B mantissa as needed to have the same exponent as A */
  manB>>=((expRes-expB)>>23);

  /* change the sign of mantissas if needed */
  if(a >> 31)
    manA *= -1;
  if(b >> 31)
    manB *= -1;

  /* sum mantissas and extract absolute value */
  int32_t man = manA + manB;
  uint32_t manRes = (man>>31)?(man*-1):man;//abs(man)

  /* shift of the mantissa if needed and consecuently adjust exponent */
  if(manRes >> 23 == 0) {
    while((manRes >> 23) == 0 && manRes != 0) {
      manRes <<= 1;
      expRes -= 0x800000;
    }
  } else if((manRes >> 24)  != 0){
    manRes >>= 1;
    expRes += 0x800000;
  }
  
  /*
   * calculation of the result:
   *  - sign is obtained by checking the mantissa before extracting the absolute value
   *  - in OR with the exponent result
   *  - in OR with the mantissa result, after masking out the 24th 1 bit
   */
  return (man<0?0x80000000:0x0) | expRes | (manRes & 0x7FFFFF);
}

//! \brief  Multiply two myFloat values
//! \param  a  first operand
//! \param  b  second operand
//! \return       product
myFloat multMyFloat(myFloat a, myFloat b) {
  /* 
   * sum of the two exponents in Excess-127 representation
   * ((a-127)+(b-127))+127 = a-127+b
   * substract 127 just once, not at the end to avoid overflow
   */
  uint32_t expRes = (a & 0x7F800000) - 0x3F800000 + (b & 0x7F800000);

  /*
   * extraction and multiplication of the two mantissas
   * mask to extract the 23 LSBs and add 1 in the 24th bit
   */
  uint64_t manA = (a & 0x7FFFFF) | 0x800000;
  uint64_t manB = (b & 0x7FFFFF) | 0x800000;
  uint32_t manRes = (manA * manB) >> 23;

  /* shift of the mantissa if needed and consecuently adjust exponent */
  if((manRes >> 24)  != 0) {
    manRes >>= 1;
    expRes+=0x800000;
  }

  /*
   * calculation of the result:
   *  - sign is obtained by XORing the two signs
   *  - in OR with the exponent result
   *  - in OR with the mantissa result, after masking out the 24th 1 bit
   */
  return ((a&0x80000000)^(b&0x80000000) ) | expRes | (manRes & 0x7FFFFF);
}



//! \brief  Check if a myFloat value is less than another one
//! \param  a  first value
//! \param  b  second value
//! \return       true if a<b, 0 else
uint8_t lessThan(myFloat a, myFloat b) {
  /* if the numbers have different sign */
  if(a>>31 != b>>31) {
    /* a can only be the smallest one if it's negative */
    return a>>31 == 1;
  }

  /* otherwise we can compare them as if they were integers
   * (the comparison will check the exponents first, then the mantissa) */
  return a < b;
}
