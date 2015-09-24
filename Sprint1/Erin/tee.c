#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
char ch;
int count=0;
int a;
int i;
char line[80];

	while ((ch = getopt(argc,argv,"ai")) != EOF)
		switch (ch) {
			case 'a':
				a=1;
				break;
			case 'i':
				i=1;
				break;
			default:
				return 1;
		}
		argc -= optind; 
		argv += optind;

	FILE *filep[argc];
	for (count=0; count <argc-1; count++) { 
		filep[count]=fopen(argv[count+1],"w");// Ignore the 'file' input
	}
	while (scanf("%79[^\n]\n", line) == 1) {
		for (count=0; count <argc-1; count++) {		
			fprintf(filep[count],"%s\n",line);
		}
		printf("%s\n",line); // Prints to stdout
	}

	for (count=0; count <argc-1; count++) { // Ignore the 'file' input
		fclose(filep[count]);
	}
}