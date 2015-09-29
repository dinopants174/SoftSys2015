#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/* This function takes as input the files the user wants the stdin to be
	put into. The user can supply a -a flag. -a appends the stdin to files
	*/
	int count = 0;	//used to loop through the user-provided files
	char ch;	//used for the options -a
	char input[1000];	//used for reading from stdin
	int a_stat;	//0 if -a option is not provided, 1 if it is
	while ((ch = getopt(argc, argv, "a")) != EOF)
		switch (ch){
			case 'a':
			a_stat = 1;	//set to 1 if -a option
			break;
		}
		argc -= optind;	//indicates that we are done dealing with the options
		argv += optind;

		scanf("%999[^\n]", input);	//reads from stdin
		printf("%s\n", input);		//prints out what was read from stdin to
		//stdout

		for (count = 0; count < argc; count++){	//loops through provided files
			if (a_stat){
				FILE *file = fopen(argv[count], "a");	//opens file with append if
				//user specified append option
				fprintf(file, "%s\n", input);	//adds input to file
				fclose(file);	//closes file, moves on to next file
				}
			
			else{
				FILE *file = fopen(argv[count], "w");	//same as above except
				//writes instead of appends
				fprintf(file, "%s\n", input);
				fclose(file);
			}		
	}
	return 0;
}