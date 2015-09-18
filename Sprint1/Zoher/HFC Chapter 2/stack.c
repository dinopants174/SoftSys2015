/* Example code for Think OS.
Copyright 2014 Allen Downey
License: GNU GPLv3
*/

/* This program has 3 functions: foo, bar, and main. foo() returns a pointer
to an array variable that contains 5 elements that are all 17. bar() does not
return anything but creates an aray and sets each element of array to its index
from 0-4. main() calls foo and stores the resulting pointer in an integer
before calling bar(). The for loop then tries to print out the value of the 
pointer variable's index.

If this program worked as expected, we should see main() printing out the
values of the array which are the indices of each element after bar() is
called.
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);  //points to some address in memory

    for (i=0; i<SIZE; i++) {
	array[i] = 17;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);  //points to the same address as foo() 

    for (i=0; i<SIZE; i++) {
	array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo(); //this is a POINTER to an array in the stack
    bar();
    printf("%p\n", array);  //this line was shows that the array pointer points
    //to the same address that foo and bar point to when they are creating
    //arrays
    for (i=0; i<SIZE; i++) {
	printf("%d\n", array[i]);
    }

    return 0;
}