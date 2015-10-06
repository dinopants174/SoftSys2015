#include <stdio.h>
#include <stdlib.h>

int main()
{
	int convert = 12;
	int store = 255;
	int res = (convert ^ store) + 1;
	printf("%i\n", res);	//will print out 244 which is -12 in 2's complement
    return 0;
}