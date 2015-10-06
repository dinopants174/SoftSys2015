#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i;
	char *input = NULL;
	unsigned long int len;
	printf("Enter a lowercase string\n");
	getline(&input, NULL, stdin);

	// for(i = 0; i < sizeof(input)/sizeof(char) - 1; i++) {
	// 	printf("%c\n", input[i]);
	// 	input[i] = (input[i] ^ 32);
	// }

	// printf("%s\n", input);

	return 0;
}
