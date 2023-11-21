#include <stdio.h>
#include <stdint.h>
void printFixed(uint32_t n) {

	printf("%#010x - %lu - %f\n",n,n,n/(16777216.0)); 

}

int main(){

uint32_t a,b,c,d;

a = 3456789435;
b = 2678901287;
c = ((uint64_t)a*b) & 0xFFFFFFFF;

d = ((uint64_t)a*b)>>32;



printf("\n\nhi%d\nlo%d\n",d,c);
/*
product gives double the bits at most

8_24
16_48 -> 16_24 but it happens that I overflow so I have to stay within 8 bits for the results -> 256

it even means that



*/
}

