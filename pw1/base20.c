#include <uart.h>
#include <or32Print.h>
#include <vgaPrint.h>

#define swapBytes( source , dest ) asm volatile ("l.nios_rrr %[out1],%[in1],r0,0x1":[out1]"=r"(dest):[in1]"r"(source));


/* *
 * Converts a given unsigned int number to string for the given base .
 *
 * @note requires (1) bufsz > 1 and (2) base > 1.
 * @note appends NUL character at the end of the output .
 * @note writes buf [0] = 0 in case of failure .
 *
 * @return int 0 in case of overflow or invalid argument , or number of
 * written characters in case of success . ( excluding NUL )
 */
unsigned int utoa (
/* * number to convert */ unsigned int number , 
/* * output buffer */ char * buf ,
/* * size of the output buffer */ unsigned int bufsz ,
/* * base ( also the length of digits ) */ unsigned int base , 
/* * digits in the base */ const char * digits
) ;


int main() {
	const char * vigesimal_digits = "0123456789ABCDEFGHIJ";
	char buf[10];
	unsigned int output;
	
	for(int number = 0; number < 1010000000000; number++) {
		output = utoa(number, buf, 10, 20, vigesimal_digits);

		or32PrintMultiple( &vgaPrintChar, &sendRs232Char, buf );
		or32PrintMultiple( &vgaPrintChar, &sendRs232Char, "\n" );

		buf[0] = output+48;
		buf[1] = '\n';
		buf[2] = 0;
		or32PrintMultiple( &vgaPrintChar, &sendRs232Char, buf );
		or32PrintMultiple( &vgaPrintChar, &sendRs232Char, "\n");
	}
}


/* *
 * Converts a given unsigned int number to string for the given base .x
 *
 * @note requires (1) bufsz > 1 and (2) base > 1.
 * @note appends NUL character at the end of the output .
 * @note writes buf [0] = 0 in case of failure .
 *
 * @return int 0 in case of overflow or invalid argument , or number of
 * written characters in case of success . ( excluding NUL )
 */
unsigned int utoa (
/* * number to convert */ unsigned int number , 
/* * output buffer */ char * buf ,
/* * size of the output buffer */ unsigned int bufsz ,
/* * base ( also the length of digits ) */ unsigned int base , 
/* * digits in the base */ const char * digits
) {	
	int i = 0, j = 0;
	char tmp[bufsz];

	if(bufsz <= 1 || base <= 1) {
		buf[0] = 0;
		return 0;
	}

	while( number != 0 ) {
		tmp[i++] = digits[number % base]; 		
		number = number / base;

		if( i > bufsz ) {
			buf[0] = 0;
			return 0;
		}
	}
	
	for(j = 0; j < i; j++) {
		buf[j] = tmp[i-j-1];
	}
	buf[j] = 0;

	return i;
}

