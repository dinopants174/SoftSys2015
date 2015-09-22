/* This function takes as input the files the user wants the stdin to be
 * put into. The user can supply a -a and -w flag. -a appends the stdin to files
 * -w writes over the original file 
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int count; //counts the terms in argv

	int opt_a = 0; //indicates whether option "a" is chosen
	int opt_w = 0; //indicates whether option "w" is chosen

	char ch; //gets the arguments
	char text[1000]; //gets the input

	while((ch = getopt(argc, argv, "aw")) != EOF)
		switch (ch) {
			case 'a':
				opt_a = 1; //set opt_a to 1 if option a is chosen
				break;
			case 'w':
				opt_w = 1; //set opt_w to 1 if option w is chosen
				break;
			default: //if the option is neither 'a' or 'w', prints out an error message
				fprintf(stderr, "Unknown option: '%s'\n", optarg);
				return 1;
		}

		//set argc and argv to the right position
		argc -= optind; 
		argv +=	optind;	

	//get input from cmd
	scanf("%79[^\t]", text);

	//based on the option, writes or appends into all the files listed
	for (count = 0; count < argc; count++) { //iterates through all the files and close them after editing
		if (opt_a) {
			FILE *file = fopen(argv[count], "a");
			fprintf(file, "%s\n", text);
			fclose(file);
		} else if (opt_w) {
			FILE *file = fopen(argv[count], "w");
			fprintf(file, "%s\n", text);
			fclose(file);
		}
	}
	return 0;
}