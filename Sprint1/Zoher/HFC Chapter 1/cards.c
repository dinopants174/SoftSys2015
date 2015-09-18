#include <stdio.h>
#include <stdlib.h>
//This is the initial cards function. The function asks for user input for a
//card. The function keeps a count based on the value of the provided card for
//a game of blackjack. If the count is high, then the user should bet and if
//the count is low, the user should not bet.
int main()
{
	char card_name[3];
	int count = 0;
	do {
		puts("Enter the card name: ");
		scanf("%2s", card_name);
		int val = 0;
		switch(card_name[0]){
			case 'K':
			case 'Q':
			case 'J':
				val = 10;	//cases K, Q, and J will go until the break
				//so they all have the value 10
				break;
			case 'A':
				val = 11;
				break;
			case 'X':
				continue;	//ends the program if the user provides X
			default:
				val = atoi(card_name);	//converts the card to an integer
				if ((val < 1) || (val > 10)){
					puts("I don't understand that value!");
					continue;
				}
		}
		if ((val>2) && (val<7)){
			count++;
		} else if (val==10){
			count--;
		}
		printf("Current count: %i \n", count);
	} while (card_name[0] != 'X');	//jupms here with Case X and ends the 
	//program
	return 0;
}