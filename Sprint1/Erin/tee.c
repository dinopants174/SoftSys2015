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
				printf("Case -a detected \n" );
				a=1;
				break;
			case 'i':
				printf("Case -i detected \n" );
				i=1;
				break;
			default:
				return 1;
		}
		argc -= optind; 
		argv += optind;

		
	// printf("%i\n",argc );
	for (count=1; count <argc; count++) { // Ignore the 'file' input
		printf("%s\n", argv[count]);
		FILE *file1=fopen(argv[count],"w");
		while (scanf("%79[^\n]\n", line) == 1) {
			fprintf(file1, "%s\n", line);
		}
		printf("done with %s\n", argv[count]);
		fclose(file1);
	}
}