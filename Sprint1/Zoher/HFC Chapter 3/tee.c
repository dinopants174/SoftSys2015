#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/* This function takes as input the files the user wants the stdin to be
	put into. The user can supply -a or -t flags. -a appends the stdin to files
	and -t is a special flag for testing this program where the user can
	provide some input that will be written to the specified files.
	*/
	int count = 0;	//used to loop through the user-provided files
	char ch;	//used for the options -a and -t
	char *input = "";	//used to hold the provided input on -t option
	char input2[100];	//used for reading from stdin
	int a_stat;	//0 if -a option is not provided, 1 if it is
	int t_stat;	//0 if -t option is not provided, 1 if it is
	while ((ch = getopt(argc, argv, "at:")) != EOF)
		switch (ch){
			case 'a':
			a_stat = 1;	//set to 1 if -a option
			break;
			case 't':
			t_stat = 1;	//set to 1 if -t option
			input = optarg;	//input contains user-provided string
			break;
		}
		argc -= optind;	//indicates that we are done dealing with the options
		argv += optind;

	scanf(" %[^\n]", input2);	//scans stdin till \n character and puts in
	//input2 which is 100 char buffer
	for (count = 0; count < argc; count++){	//loops through provided files
		if (a_stat){
			FILE *file = fopen(argv[count], "a");	//opens file with append if
			//user specified append option
			if (t_stat){
				fprintf(file, "%s\n", input); //adds input to file if -t option
			}
			fprintf(file, "%s\n", input2);	//adds input2 to file
			fclose(file);	//closes file, moves on to next file
		}
		else{
			FILE *file = fopen(argv[count], "w");	//same as above except
			//writes instead of appends
			if (t_stat){
				fprintf(file, "%s\n", input);
			}
			fprintf(file, "%s\n", input2);
			fclose(file);
		}
	}
	return 0;
}