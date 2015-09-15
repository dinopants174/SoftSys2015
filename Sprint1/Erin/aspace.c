#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5;
    void *p = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);
    
    return 0;
}

// Address of main is   0x   10b1e1e80
// Address of global is 0x   10b1e2020
// Address of local is  0x7fff54a1eb98
// Address of p is      0x7fe8c8c04a30
