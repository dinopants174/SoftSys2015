#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
	int local1 = 5;
	int local2 = 5;
	void *p1 = malloc(20);
	void *p2 = malloc(20);

	printf("Address of main is %p\n", main);
	printf("Address of global is %p\n", &global);
	printf("Address of local1 is %p\n", &local1);
	printf("Address of local2 is %p\n", &local2);
	printf("Address of p1 is %p\n", p1);
	printf("Address of p2 is %p\n", p2);

}
