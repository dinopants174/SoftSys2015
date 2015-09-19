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
		scanf("%2s",card_name);
		while((c = getchar()) != '\n' && c != EOF) //Flush the sdtin buffer
		/* discard */ ;
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
	if ((val>=2) && (val<=6)) {
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
				puts("Invalid Entry");
				puts("Number cards are between 1 and 10");
				puts("Face Cards are A, K, Q, J");
				val=0;
			}
	}	
	return val;
}

int main()
{
	int count=0;
	int val;
	char* card_name;

	card_name=init_card();

	while (card_name[0]!='X') {
		card_name=get_card();
		val=name2val(card_name);
		if (val){
			count=count_cards(val,count);
		}
		printf("Current count: %i\n", count );
	}	
 return 0;
}
