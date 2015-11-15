#include <stdio.h>
#include <stdlib.h>

char get_card(char *card_name) {
	
	puts("Enter the card_name: ");
	scanf("%2s", card_name);
	return card_name;
}

int check_card(int val, int count) {

	switch(card_name[0]) {
	case 'K':
	case 'Q':
	case 'J':
		val = 10;
		break;
	case 'A':
		val = 11;
		break;
	case 'X':
		continue;
	default:
		val = atoi(card_name);
		if ((val<1) || (val > 10)){
			puts("I don't understand bruhh");
			continue;
		}
	}
	if ((val > 2) && (val < 7)) {
		count++;
	}	else if (val == 10) {
		count--;
	}
	return count;
}

int main() {

	char card_name[3];
	int count = 0;
	while (card_name[0]!='x') {
		card_name = get_card(card_name);
		int val = 0;
		count = check_card(val,count);
		printf("Current count: %i\n", count);
	}
	return 0;
}

// int main()
// {
// 	char card_name[3];
// 	int count = 0;
// 	while (card_name[0]!='x') {
// 		puts("Enter the card_name: ");
// 		scanf("%2s", card_name);
// 		int val = 0;
// 		switch(card_name[0]) {
// 		case 'K':
// 		case 'Q':
// 		case 'J':
// 			val = 10;
// 			break;
// 		case 'A':
// 			val = 11;
// 			break;
// 		case 'X':
// 			continue;
// 		default:
// 			val = atoi(card_name);
// 			if ((val<1) || (val > 10)){
// 				puts("I don't understand bruhh");
// 				continue;
// 			}
// 		}
// 		if ((val > 2) && (val < 7)) {
// 			count++;
// 		}	else if (val == 10) {
// 			count--;
// 		}
// 		printf("Current count: %i\n", count);
// 	}
// 	return 0;
// }