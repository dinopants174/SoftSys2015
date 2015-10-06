/*
	This program is excerpt from Head First C chapter 5
	the program build a struct and increment its variable
	by one
*/
#include <stdio.h>
#include <stdlib.h>

/*
Declare a struct "turtle"
*/

typedef struct {
	const char* name;
	const char* species;
	int age;
} turtle;

/*
this function takes the turtle *, and increment its 
age by one 
*/

void happy_birthday(turtle *t) {
	(*t).age += 1; 
	printf("Happy Birthday %s! You are now %i years old!\n", t->name, t->age);
}

/*
main function 
*/

int main (int argc, char argv[]) {
	turtle m_turtle = {"Jack", "Sea Turtle", 99};
	happy_birthday(&m_turtle);
	printf("%s's age is now %i\n", m_turtle.name, m_turtle.age);
	return 0;
}

