#include <stdio.h>

/* This is the modified hello.c program that stores the value of 5 and prints
it.

THe output compiled with the -S flag and no optimization is in hello_modified.s
The output complied with the -S flag and optimization -02 is in 
hello_modified_optimized.s
*/

int main(){
	int x = 5;
	printf("%d\n", x);
}