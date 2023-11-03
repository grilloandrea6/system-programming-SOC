#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>


#define floatToMyFloat(a) (*(uint32_t *)(&(a)))
#define changeSign(a) ((a)^(0x80000000))
#define myFloatToFloat(a) (*(float *)(&(a)))

void printFloat(uint32_t n);	
uint32_t mult(uint32_t a, uint32_t b);



uint8_t lessThan(uint32_t a, uint32_t b) {
	return myFloatToFloat(a) < myFloatToFloat(b);
}

uint32_t sum(uint32_t a, uint32_t b) {
	uint32_t expA = ((a>>23) & 0xFF) - 127;
	uint32_t expB = ((b>>23) & 0xFF) - 127;
	uint32_t expRes = expA;
	
	if (((int32_t)expA) - (int32_t)expB < 0) {
		printf("inverting order\n\n");
		return sum(b,a);
	}

	uint32_t signA = a >> 31;
	uint32_t signB = b >> 31;
	
	printf("A is %s - B is %s\n",signA?"negative":"positive",signB?"negative":"positive");
	
	uint32_t signRes = 0;			
	
	int32_t manA = (int32_t)((a & 0x7FFFFF) | 0x800000); 
	int32_t manB = (int32_t)((b & 0x7FFFFF) | 0x800000); 

	printf("manA: %#0x - manB: %#0x\n",manA,manB);
	printf("manA: %d - manB: %d\n",manA,manB);
	manB >>= (expA - expB);
	
	if(signA) {printf("multiplicando A -1\n");manA *= -1;}
	if(signB) {printf("multiplicando B -1\n");manB *= -1;}
	
	printf("manA: %#0x - manB: %#0x\n",manA,manB);
	printf("manA: %d - manB: %d - - - - signed\n",manA,manB);
	printf("signA: %#0x - signB: %#0x\n",signA,signB);	
	printf("expA: %#0x - expB: %#0x\n",expA,expB);
	

	
	int32_t man = manA + manB;
	uint32_t manRes = abs(man);

	printf("man: %#0x - manRes: %#0x\n" , man, manRes);
	printf("man: %d - manRes: %d\n" , man, manRes);
	
	if(man < 0) 
	{
		printf("negative res\n");
		signRes = 1;
	}
	
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
	
	printf("expRes: %#0x\n",expRes);
	uint32_t res = (signRes << 31) | ((expRes+127)<<23) | (manRes & 0x7FFFFF);
	return res;
}









int main(){
	/*float af = 3133.225, bf = -7.3;
	
	uint32_t *a = &af, *b = &bf;
	
	uint32_t res = sum(*a,*b);
	
	float *resf = &res;
	printf("%f should be %f\n\nprintFloat\n",*resf,af+bf);
	printFloat(res);
	
	printf("\n\nactual print float\n");
	printFloat(af+bf);
	
	printf("\n\nb operand printFloat\n");
	printFloat(bf);
	//printFloat(res);
	//wait(300);	
		printf (" The random number is: %d", rand()); */
		
		
	srand( time(NULL)); 

	uint32_t resProd,resSum;
	float limit = 2000.0;
	int eddai = 1;
	while(eddai) { 
	eddai = 0;
		printf("-------------------------------------------------------------------------------\n");   
   float A = 0.005859375;
   float B = 4;
	//	float A = (float)rand()/(float)(RAND_MAX/limit) - limit/2; 
	//	float B = (float)rand()/(float)(RAND_MAX/limit) - limit/2; 

		float randomA = A;
		float randomB = B;

		printf( " Random numberA = %f\n", randomA);   
		printf( " Random numberB = %f\n", randomB);  
		printf("SUM - %f\n",A+B);
		

		printf("\n\n printing float A\n");
		printFloat(floatToMyFloat(randomA));
		
		printf("\n\n printing opposite of float A\n");
			printFloat(changeSign(floatToMyFloat(randomA)));
				
		printf("\n\n printing float B\n");
		printFloat(floatToMyFloat(randomB));
		
		
		printf("\n\n printing lessThan(A,B)\n");
		printf(lessThan(floatToMyFloat(randomA),floatToMyFloat(randomB))?"true\n\n":"false\n\n");
		
		
		
		
		
		printf("\n\n\n SUM");
		
		resSum = sum(floatToMyFloat(randomA),floatToMyFloat(randomB));
		printFloat(resSum);
				
		printf("\n\n\n PROD");
	
		resProd = mult(floatToMyFloat(randomA),floatToMyFloat(randomB));
		printFloat(resProd);
		
		printf("\n\n\n ");		
		
		
		//printf("SUM - %f should be %f - - - delta %f\n\n\n\n\n",*(&resSum),(float)A+(float)B, *(&resSum) - (A+B));
		//printf("PROD - %f should be %f - - - delta %f\n\n\n\n\n",*(&resProd),A*B, *(&resProd) - (A*B));
		

		/*
		if(abs((float)((*(&resSum))) - (float)(A+B)) > 0.1) { 
			printf(" - - -  - - - - - - -  -ERROR SUM - - - -  -- - - - \n\n\n\n\n\n\n");
			//break;
		}
		
		if(abs((*(&resProd)) - (A*B)) > 0.1){ 
			printf(" - - -  - - - - - - -  -ERROR PROD - - - -  -- - - - \n\n\n\n\n\n\n");
			break;
		}*/

		
		
		//sleep(1);
	}
}



uint32_t mult(uint32_t a, uint32_t b)
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

	printf("signA: %#0x - signB: %#0x\n",signA,signB);	
	printf("manA: %#0x - manB: %#0x\n",manA,manB);
	printf("manA: %d - manB: %d\n",manA,manB);
	printf("expA: %#0x - expB: %#0x\n",expA,expB);
	
	signRes = signA ^ signB;			
	
	manLong = (uint64_t)manA * (uint64_t)manB;							//!!!!
	//manLong = manA * manB;							//!!!!
	manRes = (uint32_t)(manLong >> 23);	

	expRes = expA + expB;
	
	printf("manLong: %#0x - manRes: %#0x\n" , manLong, manRes);
	printf("manLong: %d - manRes: %d\n" , manLong, manRes);
	
	printf("expRes: %#0x\n",expRes);
	
	
	//ToDo riscalare!!!
	printf("---%#0x---\n",manRes);
	if(manRes == 0)
		printf("cazzo abbiamo azzerato!");
		
		
		
	if(manRes >> 23 == 0) {
		while((manRes >> 23) == 0) {
			manRes <<= 1;
			expRes--;
			//printf("m");
		}
	} else {
		while((manRes >> 24)  != 0) {
			manRes >>= 1;
			expRes++;
			//printf("e");
		}
	}
	// se la parte maggiore che deve esserre nulla piu msb `e nulla
	// 	ciclo shift a sx finche msb 1
	// altrimenti
	//	ciclo shift a dx fino a che tutta la parte che deve essere zero e nulla
	
	uint32_t res = (signRes << 31) | ((expRes+127)<<23) | (manRes & 0x7FFFFF);
	return res;
}


void printFloat(uint32_t n) {//works in [-511.99-511.99] - then there is some overflow error but I don't understand where

	printf("raw number: - - - - - - - - %#0x\n",n);

	// print sign
	if(n & 1<<31)
		printf("negative number\n");
	
	int32_t exp = ((n & 0x7F800000) >> 23) - 127;
	uint32_t mantissa = (n & 0x7FFFFF) + (1<<23);
	printf("original mantissa: %#0x - %d - %f \n", mantissa, mantissa, ((float)mantissa)/8388608.0);
	
	printf("exponent: %#0x\n",exp);
	
	uint64_t number = mantissa <<exp;

	printf("number: %c%f \n", (n & 1<<31) ? '-' : ' ' ,((float)number)/8388608.0);
}


/*
uint32_t mult(uint32_t a, uint32_t b) {
	uint32_t res = 0;
	
	/* 
	truth table for signs, should be a XOR
	a b res
	0 0 0
	0 1 1
	1 0 1
	1 1 0
	
	
	// sign calculation with a XOR
	res = (a & 1<<31) ^ (b & 1<<31);
	 
	 
	// multiply mantissa -> this way I can have overflow, I have to do it in another variable, then rescale and put it here, but i'll give it a try
	res |= ( ((a & 0x7FFFFF) + (1<<23)) * ((b & 0x7FFFFF)+(1<<23)) ) & 0x7FFFFF;
	
	// sum exponents
	res |= (((((a & 0x7F800000) >> 23) - 127) + (((b & 0x7F800000) >> 23) - 127)) + 127) << 23 ;
	
	
	return res;
}
*/

