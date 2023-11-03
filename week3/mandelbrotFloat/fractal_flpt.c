#include "fractal_flpt.h"
#include <or32Print.h>
#include <vgaPrint.h>


#define swapBytes( source , dest ) asm volatile ("l.nios_rrr %[out1],%[in1],%[in2],0x1":[out1]"=r"(dest):[in1]"r"(source), [in2]"r"(1));

//! \brief  Mandelbrot fractal point calculation function
//! \param  cx    x-coordinate
//! \param  cy    y-coordinate
//! \param  n_max maximum number of iterations
//! \return       number of performed iterations at coordinate (cx, cy)
uint16_t calc_mandelbrot_point_soft(myFloat cx, myFloat cy, uint16_t n_max) {
  /*myFloat x = cx;
  myFloat y = cy;
  float fourF = 4.0f;
  myFloat four = floatToMyFloat(fourF);

     or32PrintMultiple(&vgaPrintChar, "point\n");
 float twoF = 2.0f;
  myFloat two = floatToMyFloat(twoF);
  uint16_t n = 0;
  myFloat xx, yy, two_xy;
  do {
  
    xx = multMyFloat(x,x);
    yy = multMyFloat(y,y);
    two_xy = multMyFloat(two,multMyFloat(x,y)); //ToDo

    x = sumMyFloat(sumMyFloat(xx,cx),changeSign(yy)); //ToDo
    y = sumMyFloat(two_xy, cy);
    ++n;
  } while (lessThan(sumMyFloat(xx, yy),four) && (n < n_max));
  return n;*/
  return 64;
}


//! \brief  Map number of performed iterations to black and white
//! \param  iter  performed number of iterations
//! \param  n_max maximum number of iterations
//! \return       colour
rgb565 iter_to_bw(uint16_t iter, uint16_t n_max) {
  if (iter == n_max) {
    return 0x0000;
  }
  return 0xffff;
}


//! \brief  Map number of performed iterations to grayscale
//! \param  iter  performed number of iterations
//! \param  n_max maximum number of iterations
//! \return       colour
rgb565 iter_to_grayscale(uint16_t iter, uint16_t n_max) {
  if (iter == n_max) {
    return 0x0000;
  }
  uint16_t brightness = iter & 0xf;
  rgb565 res;
  swapBytes(((brightness << 12) | ((brightness << 7) | brightness<<1)), res);
  return res;
}


//! \brief Calculate binary logarithm for unsigned integer argument x
//! \note  For x equal 0, the function returns -1.
int ilog2(unsigned x) {
  if (x == 0) return -1;
  int n = 1;
  if ((x >> 16) == 0) { n += 16; x <<= 16; }
  if ((x >> 24) == 0) { n += 8; x <<= 8; }
  if ((x >> 28) == 0) { n += 4; x <<= 4; }
  if ((x >> 30) == 0) { n += 2; x <<= 2; }
  n -= x >> 31;
  return 31 - n;
}


//! \brief  Map number of performed iterations to a colour
//! \param  iter  performed number of iterations
//! \param  n_max maximum number of iterations
//! \return colour in rgb565 format little Endian (big Endian for openrisc)
rgb565 iter_to_colour(uint16_t iter, uint16_t n_max) {
  if (iter == n_max) {
    return 0x0000;
  }
  uint16_t brightness = (iter&1)<<4|0xF;
  uint16_t r = (iter & (1 << 3)) ? brightness : 0x0;
  uint16_t g = (iter & (1 << 2)) ? brightness : 0x0;
  uint16_t b = (iter & (1 << 1)) ? brightness : 0x0;
  rgb565 res;
  swapBytes(((r & 0x1f) << 11) | ((g & 0x1f) << 6) | ((b & 0x1f)), res);
  return res;
}

rgb565 iter_to_colour1(uint16_t iter, uint16_t n_max) {
  if (iter == n_max) {
    return 0x0000;
  }
  uint16_t brightness = ((iter&0x78)>>2)^0x1F;
  uint16_t r = (iter & (1 << 2)) ? brightness : 0x0;
  uint16_t g = (iter & (1 << 1)) ? brightness : 0x0;
  uint16_t b = (iter & (1 << 0)) ? brightness : 0x0;
  rgb565 res;
  swapBytes(((r & 0xf) << 12) | ((g & 0xf) << 7) | ((b & 0xf)<<1), res);
  return res;
}

//! \brief  Draw fractal into frame buffer
//! \param  width  width of frame buffer
//! \param  height height of frame buffer
//! \param  cfp_p  pointer to fractal function
//! \param  i2c_p  pointer to function mapping number of iterations to colour
//! \param  cx_0   start x-coordinate
//! \param  cy_0   start y-coordinate
//! \param  delta  increment for x- and y-coordinate
//! \param  n_max  maximum number of iterations
/*void draw_fractal(rgb565 *fbuf, int width, int height,
                  calc_frac_point_p cfp_p, iter_to_colour_p i2c_p,
                  myFloat cx_0, myFloat cy_0, myFloat delta, uint16_t n_max) {
  rgb565 *pixel = fbuf;
  myFloat cy = cy_0;
  for (int k = 0; k < height; ++k) {
     or32Print(&vgaPrintChar, "row %d\n",k);
    myFloat cx = cx_0;
    for(int i = 0; i < width; ++i) {
      uint16_t n_iter = (*cfp_p)(cx, cy, n_max);
      rgb565 colour = (*i2c_p)(n_iter, n_max);
      *(pixel++) = colour;
      cx = sumMyFloat(cx,delta);//cx += delta;
    }
    cy = sumMyFloat(cy,delta);//cy += delta;
  }
}*/

void draw_fractal(rgb565 *fbuf, int width, int height,
                  calc_frac_point_p cfp_p, iter_to_colour_p i2c_p,
                  myFloat cx_0, myFloat cy_0, myFloat delta, uint16_t n_max) {
  rgb565 *pixel = fbuf;


      uint16_t n_iter = (*cfp_p)(.0f, .0f, n_max);
      rgb565 colour = (*i2c_p)(n_iter, n_max);

//or32Print(&vgaPrintChar, "HEIGH %d\n",height);

  for (int k = 0; k < height; ++k) {
     or32Print(&vgaPrintChar, "row %d\n",k);
    //myFloat cx = cx_0;
    for(int i = 0; i < width; ++i) {

      *(pixel++) = colour;
      //cx = sumMyFloat(cx,delta);//cx += delta;
    }
    //cy = sumMyFloat(cy,delta);//cy += delta;
  }
}





uint32_t sumMyFloat(uint32_t a, uint32_t b) {
	uint32_t expA = ((a>>23) & 0xFF) - 127;
	uint32_t expB = ((b>>23) & 0xFF) - 127;
	uint32_t expRes = expA;
	
	if (((int32_t)expA) - (int32_t)expB < 0)
		return sumMyFloat(b,a);

	uint32_t signA = a >> 31;
	uint32_t signB = b >> 31;
	uint32_t signRes = 0;			
	
	int32_t manA = (int32_t)((a & 0x7FFFFF) | 0x800000); 
	int32_t manB = (int32_t)((b & 0x7FFFFF) | 0x800000); 

	manB >>= (expA - expB);
	
	if(signA) 
		manA *= -1;
	if(signB) 
		manB *= -1;
	
	int32_t man = manA + manB;
	uint32_t manRes = (man>>31)?(man*-1):man;//abs(man)

	if(man < 0) 
		signRes = 1;
	
	// rescaling
	if(manRes >> 23 == 0) {
		while((manRes >> 23) == 0) {
			manRes <<= 1;
			expRes--;
		}
	} else {
		while((manRes >> 24)  != 0) {
			manRes >>= 1;
			expRes++;
		}
	}

	uint32_t res = (signRes << 31) | ((expRes+127)<<23) | (manRes & 0x7FFFFF);
	return res;
}



uint32_t multMyFloat(uint32_t a, uint32_t b)
{
	uint32_t expA = ((a>>23) & 0xFF) - 127;
	uint32_t expB = ((b>>23) & 0xFF) - 127;
	uint32_t expRes;

	uint32_t signA = a >> 31;
	uint32_t signB = b >> 31;
	uint32_t signRes;			

	int32_t manA = (int32_t)((a & 0x7FFFFF) | 0x800000); 
	int32_t manB = (int32_t)((b & 0x7FFFFF) | 0x800000); 
	uint64_t manLong;
	//uint32_t manLong;
	uint32_t manRes;

	signRes = signA ^ signB;			
	
	manLong = (uint64_t)manA * (uint64_t)manB;							//!!!!
	//manLong = manA * manB;							//!!!!
	manRes = (uint32_t)(manLong >> 23);	

	expRes = expA + expB;
	
	//ToDo riscalare!!!
	if(manRes >> 23 == 0) {
		while((manRes >> 23) == 0) {
			manRes <<= 1;
			expRes--;
		}
	} else {
		while((manRes >> 24)  != 0) {
			manRes >>= 1;
			expRes++;
		}
	}
	// se la parte maggiore che deve esserre nulla piu msb `e nulla
	// 	ciclo shift a sx finche msb 1
	// altrimenti
	//	ciclo shift a dx fino a che tutta la parte che deve essere zero e nulla
	
	uint32_t res = (signRes << 31) | ((expRes+127)<<23) | (manRes & 0x7FFFFF);
	return res;
}



uint8_t lessThan(myFloat a, myFloat b) {
	return myFloatToFloat(a) < myFloatToFloat(b);
}
