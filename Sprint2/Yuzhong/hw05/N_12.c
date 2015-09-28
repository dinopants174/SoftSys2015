#include <stdio.h>

int main () {
	//assign 12 to 'x' and perform XOR operation on 'x' to see if we can get -12
	int x = 12;
	int y = (12 ^ -1);
	int z = y + 1;

	printf("The original value is %d\n", x);
	printf("the value after XOR operation is %d\n", y);
	printf("and the value after plus 1 is %d\n", z);

	return 0;
}