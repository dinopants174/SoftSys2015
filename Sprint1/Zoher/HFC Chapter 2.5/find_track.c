/* Example code for Software Systems at Olin College.
Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    regex_t re; //hold a compiled regular expression
    int regcomp_status; //0 if it runs successfully, has a value if there is an
    //error
    int regexec_status; //same as above
    char regcomp_buffer[100];   //buffer to hold actual error messages
    char regexec_buffer[100];
    int i;

    regcomp_status = regcomp(&re, pattern, REG_EXTENDED);   //compiles the user
    //inputted pattern
    if (regcomp_status){    //status is 0 if regcomp runs sucessfully, if it doesn't we call our error interpreter function
        regerror(regcomp_status, &re, regcomp_buffer, 100); //generates a
        //string containing the error message
        printf("regcomp() failed with '%s'\n", regcomp_buffer);
    }

    for (i=0; i<NUM_TRACKS; i++){   //loop through all the tracks calling
        //regexec to see fi the pattern is in each track
        regexec_status = regexec(&re, tracks[i], (size_t) 0, NULL, 0);
        //searches for pattern
        if (regexec_status){    //status is 0 if regexec runs successfully, if it doesn't we call our error interpreter function
            regerror(regexec_status, &re, regexec_buffer, 100);
            printf("regexec() failed with '%s'\n", regexec_buffer);
            //prints out no match error if pattern not in track
        }
        else{
            printf("Track %i: '%s'\n", i, tracks[i]);   //prints out track if
            //pattern found in track 
        }
    }
    regfree(&re);   //frees up allocated memory regcomp put in re
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];
    char pattern[80];
    /* take input from the user and search */
    printf("Search for pattern: ");
    fgets(pattern, 80, stdin);
    rstrip(pattern);
    find_track_regex(pattern);

    // printf("Search for: ");
    // fgets(search_for, 80, stdin);
    // rstrip(search_for);

    // find_track(search_for);
    //find_track_regex(search_for);

    return 0;
}