#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char* name;
	const char* species;
	int age;
} turtle;

void happy_birthday(turtle *t) {
	(*t).age += 1; 
	printf("Happy Birthday %s! You are now %i years old!\n", t->name, t->age);
}

int main (int argc, char argv[]) {
	turtle m_turtle = {"Jack", "Sea Turtle", 99};
	happy_birthday(&m_turtle);
	printf("%s's age is now %i\n", m_turtle.name, m_turtle.age);
	return 0;
}

