#include <stdio.h>
#include <stdlib.h>
int main()
{
	char card_name[3];
	int count =0;
	int val =0;
	while (val) {
		puts("Enter the card name:");
		scanf("%2s",card_name);
		switch(card_name[0]) {
			case 'K':
			case 'Q':
			case 'J':
				val= 10;
				break;
			case 'A':
				val=11;
				break;
			case 'X':
				val=0;
				break;
			default:
				val=atoi(card_name);
				if ((val <0) || val >10) {
					puts("Number cards are between 1 and 10");
					continue;
				}
		}	
		if ((val>=3) && (val<=6)) {
			count++;
		} else if (val==10) {
			count--;
		}
		printf("Current count: %i\n", count );
	}
 return 0;
}