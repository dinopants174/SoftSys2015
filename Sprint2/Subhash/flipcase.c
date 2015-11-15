#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *arg[])
{
    int u;
    int flip = 32;      //flipping using the 6th bit, 32 in binary is 100000
    char input[800];
    printf("lower-case string:\n");
    scanf("%8s\n", input);

    for(u=0;u<sizeof(input);u++)
    {
    	if (input[u] =='\0') {         //break once at the end of string
            break;
        }
        input[u] = (input[u]^flip);    //xor w/ 32 flips 6th bit
    }

    printf("%s\n", input);
    return 0;
}