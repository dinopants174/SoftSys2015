/*==================================
Cards.c

This program asks user for card name 
and prints out their chance to win

Valid card inputs are: 
2, 3, 4, 5, 6, 7, 8, 
9, 10, J, Q, K, A, X

if either one of 10, J, Q, K 
is typed by user, count goes down 
by one. if 3, 4, 5, 6 is received,
count goes down by 1.

if 'X' is received, exit the program

Author: Yuzhong Huang
Copyright: Yuzhong Huang
Date: 9/9/2015
Last Modified: 9/12/2015

==================================*/

#include <stdio.h>
#include <stdlib.h>

/*
declaring functions
*/

void getCardValue(int * val, int *notX, char *ch, char *prompt);
void getCardName(char *ch, char *prompt);
void updateCount(int val, int *count);
int isValid(int val);

int main () {

	/*
	initializing parameters
	*/

	char card_name[3];	//this variable stores the value of user's input
	char *promptInput = "Enter the card_name: ";  //string value prompts to user for input
	char *promptInval = "I don't understand the value!"; // string value prompts to user if the card is invalid
	int count = 0;	//this variable indicates the chance of winning.
	int val = 0;   //variable 'val' stores the numerical value of a card
	int notX = 1; //indicates whether the user types in 'X' to exit the program



	/*
	a loop in which continues to prompt the user for input until a 'X' is received
	*/

	while(notX) {
		getCardName(card_name, promptInput);
		getCardValue(&val, &notX, card_name, promptInval);

		/*
		if user types in 'X', skip that part
		*/

		if (notX)
		{
		updateCount(val, &count);
		}
	};

	return 0;
}

/* Changes the value of variable "val" according to 
   the value in ch, If user types in 'X', 
   change the value of "notX" to '0' 

   val: the numerical value of the current card
   notX: indicates whether the program should exit
   ch: buffer where card name is stored
   prompt: string prompt to display
*/  

void getCardValue(int *val, int *notX, char *ch, char *prompt) {
	switch (ch[0]) {
		case 'K':
		case 'Q':
		case 'J':
			*val = 10;
			break;		
		case 'A': 
			*val = 11;
			break;
		case 'X':
			*notX = 0;
			break;
		default:
			*val = atoi(ch);
			if (!isValid(*val)) {
				puts(prompt);
			} 
	}
}

/* Asks for user's input and puts the reply in a given buffer

   User input is truncated to the first two characters

   ch: buffer where result is stored
   prompt: string prompt to display
*/
void getCardName(char * ch, char * prompt) {
	puts(prompt);
	scanf("%2s", ch);
}

/* Updates the count and prints out the value of 'count'

   val: the numerical value of the current card
   count: indicates chance to win
*/
void updateCount(int val, int * count) {
	if ((val > 2) && (val < 7)) (*count)++;
	if (val == 10) (*count)--;
	printf("current count: %i\n", *count);
}

/* this function checks whether user's input is valid

   cards are valid if their atoi value is between 1 and 10
   
   val: the numerical value of the current card
*/
int isValid(int val) {
	return (val > 1 && val <= 10);
}
