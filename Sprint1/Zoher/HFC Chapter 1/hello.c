#include <stdio.h>

/* This is the initial hello.c program with the additional line int x=5 added.

The output compiled with the -S flag and no optimization is in hello.s
The output complied with the -S flag and optimization -02 is in hello_optimized.s
*/

int main(){
	int x = 5;
	printf("Hello World\n");
}