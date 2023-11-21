#include <uart.h>
#include <or32Print.h>
#include <vgaPrint.h>
#include <stdint-gcc.h>

const int32_t a = 3 <<24; //!< default fractal width 
const int32_t b = -2<<24;      //!< default start x-coordinate 
const int32_t c = (int32_t)(-1.5 * 16777216.0);      //!< default start y-coordinate 



int main() {
	//int a = 3;
	//int b = 4;
	int32_t test = ((int64_t)a * (int32_t)c)>>24;



	or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "\nA: decimal %d\n hex %X\n ",a,a);
	or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "\nC: decimal %d\n hex %X\n ",c,c);
	or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "\nTEST: decimal %d\n hex %X\n ",test,test);

/*	int reshi = 5;
	int reslo = 5;

	asm ("l.mac %[a],%[b]" :: [a]"r"(a),[b]"r"(b));

	asm ("l.mfspr %[res],r0,10242": [res]"=r"(reshi));
	//asm ("l.mfspr %[res],r0,10241": [res]"=r"(reslo));
	asm ("l.macrc %[res]": [res]"=r"(reslo));
	or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "eddai\n%d\naa\n",reshi);
	or32PrintMultiple(&vgaPrintChar, &sendRs232Char, "eddai\n%d\naa\n",reslo);
//multFx(a,b);
//getHi(res);
//asm ("l.mac %[a],%[b]" :: [a]"r"(a),[b]"r"(b));
//asm ("l.mac %[a],%[b]" :: [a]"r"(a),[b]"r"(b));

*/
//int c = a * b;
/*	or32PrintMultiple( &vgaPrintChar, &sendRs232Char, "start\n" );
	or32PrintMultiple( &vgaPrintChar, &sendRs232Char, "%d %d\n",sizeof(int),sizeof(short));
	
	
int a,b,c,d;
a =  7.303 *   0x1000000;
b =  35.002 * 0x1000000;

c = a+b;

d = ((int)a*b)>>24;

printFixed(a);
printFixed(b);
printFixed(c);
printFixed(d);

	
	
	or32PrintMultiple( &vgaPrintChar, &sendRs232Char, "end\n" );
*/}
