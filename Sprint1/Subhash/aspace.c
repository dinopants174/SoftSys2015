/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

int funky ()
{
	int funk = 13;
	printf ("Address of funk is %p\n", &funk);
	return 0;
}

int main ()
{
    int local = 5;
    void *p = malloc(128);
    void *q = malloc(128);
    void *x = malloc(33);
    void *y = malloc(33);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    funky();
    printf ("Address of p is %p\n", p);
    printf ("Address of q is %p\n", q);
    printf ("Address of x is %p\n", x);
    printf ("Address of y is %p\n", y);
    
    return 0;
}
