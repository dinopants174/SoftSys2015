#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5;
    int local2=6;
    void *p = malloc(20);
    void *q = malloc(20);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of local2 is %p\n", &local2);
    printf ("Address of p is %p\n", p);
    printf ("Address of q is %p\n", q);
    
    return 0;
}

// Address of main is   0x   106f1de10
// Address of global is 0x   106f1e020
// Address of local is  0x7fff58ce2b98
// Address of local2 is 0x7fff58ce2b94
// Address of p is      0x7fdc63c04a30
// Address of q is      0x7fdc63c04ab0
