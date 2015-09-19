/* My version of the Code in HFC that has the user input
card names, and then counts how hot the deck is. */

#include <stdio.h>
#include <stdlib.h>


char* get_card() {
//Asks the user to input a card, but returns
//only the first two characters
		int c;
		static char card_name[3];
		puts("Enter the card name:");
		// fgets(card_name,3,stdin);
		scanf("%2s",card_name);
		while((c = getchar()) != '\n' && c != EOF) //Flush the sdtin buffer
		/* discard */ ;
		printf("Current card inside f: %s\n", card_name);
		return card_name;
}

char* init_card() {
//No moar segmenation faults plz
		static char card_name[3];
		return card_name;
}

int count_cards(val,count) {
// Updates the count of the deck based on the
// value of the current card
	if ((val>=3) && (val<=6)) {
			count++;
		} else if ((val==10) || (val==11)){
			count--;
		}
	return count;
}

int name2val(char* card_name){
	int val;
	switch(card_name[0]) {
		case 'K':
		case 'Q':
		case 'J':
			val= 10;
			break;
		case 'A':
			val=11;
			break;
		default:
			val=atoi(card_name);
			if ((val <1) || (val >11)) {
				puts("Number cards are between 1 and 10");
				puts("Face Cards are A, K, Q, J");
				val=0;
			}
	}	
	
	return val;
}
int main()
{
	// char card_name[3];
	int count=0;
	int val;
	char* card_name;
	int loop=0;

	card_name=init_card();

	while (card_name[0]!='X') {
		printf("Loop: %i\n", loop);
		card_name=get_card();
		printf("Current card: %s\n", card_name);
		val=name2val(card_name);
		printf("Current val: %i\n", val);
		if (val){
			count=count_cards(val,count);
		}
		printf("Current count: %i\n", count );
		loop++;
	}

	
 return 0;
}
