#include <stdio.h>
#include <stdlib.h>

int global;

int stack_grow_down(){
	/* This function doesn't take any inputs and adds a local variable to the stack. The function prints 
	*/
	int x = 5;
	printf("Address of another local variable is %p\n", &x);
	printf("The stack has grown down\n");
	return 0;
}

int main()
{
	int local = 5;
	void *heap1 = malloc(128);
	void *heap2 = malloc(128);

	int rando = 16;
	void *rando1 = malloc(rando);
	void *rando2 = malloc(rando);

	printf("-----------------------\n");
	printf("Address of main is %p\n", main);
	printf("Address of global is %p\n", &global);
	printf("-----------------------\n");
	printf("Address of local is %p\n", &local);
	stack_grow_down();
	printf("-----------------------\n");
	printf("Address of heap1 is %p\n", heap1);
	printf("Address of heap2 is %p\n", heap2);
	printf("The heap has grown up\n");
	printf("-----------------------\n");
	printf("Address of rando1 is %p\n", rando1);
	printf("Address of rando2 is %p\n", rando2);
	printf("The difference between them is 16 which is the size allocated per rando\n");
	printf("-----------------------\n");

	return 0;
}
