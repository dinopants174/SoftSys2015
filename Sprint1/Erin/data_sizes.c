#include <stdio.h> 
#include <limits.h> 
#include <float.h>

int main() {
	printf("The value of INT_MAX is %i\n", INT_MAX); 
	printf("The value of INT_MIN is %i\n", INT_MIN); 
	printf("An int takes %lu bytes\n", sizeof(int));
	printf("The value of FLT_MAX is %f\n", FLT_MAX); 
	printf("The value of FLT_MIN is %.50f\n", FLT_MIN);
	printf("A float takes %lu bytes\n", sizeof(float));
	printf("The value of CHAR_MAX is %i\n", CHAR_MAX); 
	printf("The value of CHAR_MIN is %i\n", CHAR_MIN); 
	printf("A char takes %lu bytes\n", sizeof(char));
	printf("The value of DBL_MAX is %f\n", DBL_MAX); 
	printf("The value of DBL_MIN is %f\n", DBL_MIN); 
	printf("A double takes %lu bytes\n", sizeof(double));
	printf("The value of SHRT_MAX is %i\n", SHRT_MAX); 
	printf("The value of SHRT_MIN is %i\n", SHRT_MIN); 
	printf("A short takes %lu bytes\n", sizeof(short));
	printf("The value of LNG_MAX is %li\n", LONG_MAX); 
	printf("The value of LNG_MIN is %li\n", LONG_MIN); 
	printf("A long takes %lu bytes\n", sizeof(long));
return 0; }


// The value of INT_MAX is 2147483647
// The value of INT_MIN is -2147483648
// An int takes 4 bytes
// The value of FLT_MAX is 340282346638528859811704183484516925440.000000
// The value of FLT_MIN is 0.00000000000000000000000000000000000001175494350822
// A float takes 4 bytes
// The value of CHAR_MAX is 127
// The value of CHAR_MIN is -128
// A char takes 1 bytes
// The value of DBL_MAX is 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000
// The value of DBL_MIN is 0.000000
// A double takes 8 bytes
// The value of SHRT_MAX is 32767
// The value of SHRT_MIN is -32768