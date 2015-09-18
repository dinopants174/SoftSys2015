#include <stdio.h>

/* This is the modified hello.c program that stores the value of 5 in x and sets
int y to 5+1 and then prints out the value of y.

THe output compiled with the -S flag and no optimization is in hello_modified2.s
The output complied with the -S flag and optimization -02 is in 
hello_modified2_optimized.s
*/

int main(){
	int x = 5;
	int y = x+1;
	printf("%d\n", y);
}