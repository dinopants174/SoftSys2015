/*
	this program uppercase an input lowercase string
	by performing bit operation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	remove() replace the \n character with an '\0'
	to end the string
*/

void remove(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main(int argc, char *argv[]){
	int i;
	char input[80]; 
    printf("Convert from lower-case to upper: ");
    fgets(input, 80, stdin);
    rstrip(input);

    for (i = 0; i <= sizeof(input) -1; i++){
        if (input[i] == '\0'){
            break;  //checks to see if we hit the null character which means the string is done
        }
    	char c = input[i];
    	int ic = c;
        if (ic != 32){  //checks if character is not a space
    	   if ((ic >> 5) & 1){  //checks if the 6th bit is 1, means lower-case
    		  ic ^= (1u << 5);    //flips the value of the 6th bit to 0 if 1
    	   }
        }
    	char res = ic;
    	printf("%c", res);
    }

    return 0;
}