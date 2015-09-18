#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Prompts the user to input a card. User input is checked to see if the input
is valid. If the user input is valid, the card is then assigned a value. The
value of each card affects a count which informs the user whether or not they
should bet in a game of a blackjack. If the count is high, the user should bet
high. If the count is low, the user should bet low.

This program compiled with gcc -ansi -pendatic -Wall does not generate any
additional warnings*/
bool card_prep(char *letter){
	/*This function takes as input the card given by the user.

	The function checks if the card is an expected input.
	
	The function returns a boolean, true if the card is valid input and false
	if the card is not valid.
	*/
	bool is_valid = 0;
	if ((letter[0] == 'K') || (letter[0] == 'Q') || (letter[0] == 'J') || (letter[0] == 'A')){
		is_valid = 1;
	}
	else{
		int check = 0;
		check = atoi(letter);
		if ((check < 1) || (check > 10)){
			is_valid = 0;
		}
		else{
			is_valid = 1;
		}
	}
	return is_valid;
}

int assign_val(char *letter){
	/*This function takes as input the card given by the user.

	The function checks the first character in the array provided by the user
	and assigns a value to the card.

	The function then returns the value.
	*/
	int val = 0;
	switch(letter[0]){
		case 'K':
		case 'Q':
		case 'J':
			val = 10;
			break;
		case 'A':
			val = 11;
			break;
		default:
			val = atoi(letter);
	}
	return val;
}

int counter(int count, int val)
	/*This function takes as input the current count and the value of the card.

	This function increments or decrements the count based on the value of the
	card.

	The function then returns the count.
	*/
{
	if ((val > 2) && (val < 7)){
		count++;
	} else if (val==10){
		count--;
	}
	return count;
}

int main()
	/* This function asks the user to enter a card, checks if the provided card
	is valid, assigns a value to the card if it is valid, and increments or
	decrements the count based on the value.

	If the card is not valid, the program tells the user the input is invalid
	and asks the user to try again.
	*/
{
	char card_name[3];
	int val = 0;
	int count = 0;
	bool is_valid = 0;
	do {
		puts("Enter the card name: ");
		scanf("%2s", card_name);
		is_valid = card_prep(card_name);
		if (is_valid){
			val = assign_val(card_name);
			count = counter(count, val);
			printf("Current count: %i \n", count);
		}
		else if (card_name[0] == 'X'){
			continue;
		}
		else{
			puts("That is not a valid card. Please try again.");
			continue;
		}
	} while (card_name[0] != 'X');
	return 0;
}

