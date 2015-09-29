#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i;
	char input[100];
	printf("Enter a lowercase string\n");
	scanf("%8s\n", input);

	for(i = 0; i < sizeof(input); i++) {
		input[i] = (input[i] ^ 32);
	}

	printf("%s\n", input);

	return 0;
}
