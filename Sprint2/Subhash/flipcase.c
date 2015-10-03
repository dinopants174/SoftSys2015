#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *arg[])
{
    int u;
    int flip = 32;
    char input[100];
    printf("lower-case string:\n");
    scanf("%8s\n", input);

    for(u=0;u<sizeof(input);u++)
    {
    	input[u] = (input[u]^flip);
        if (input[u] =="\0") {
            break;
        }
    }

    printf("%s\n", input);
    return 0;
}