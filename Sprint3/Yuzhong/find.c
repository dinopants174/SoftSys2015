/*
	This program is excerpt from Head First C chapter 6.
	
	The find() function tracks down all the sports fans
	in the list who don't also share a passion for 
	bieber

	Author: Yuzhong
	Written: 10/17/2015
*/ 
#include <stdio.c>
#include <stdlib.h>

/*
	function declaration
*/

void find();
int sports_no_bieber(char *s);

int main (int argc, String[] args) {

	find();
}

void find(int (*match)(char *)) {
	int i;
	puts("Search results: ");
	puts("--------------------------------------");

	for (i = 0; i < NUM_ADS; i++) {
		if (match(ADS[i])) {
			printf("%s\n", ADS[i]);
		}
	}

	puts("--------------------------------------");
}

int sports_no_bieber(char *s)
{
return strstr(s, "sports") && !strstr(s, "bieber");
}