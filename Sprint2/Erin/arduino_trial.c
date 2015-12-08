
#include <stdio.h>
#include <stdlib.h>

struct note{
	int comp;
};

struct note *make_note(int val) {
    struct note *node = malloc(sizeof(struct note));
    node->comp = val;
    return node;
}
int main() {
	struct note *C=make_note(261);
	struct note *Cs=make_note(20);	
	struct note Notelist[2]={*C,*Cs};
	printf("%i\n", (&Notelist[1])->comp);
	printf("%lu\n",sizeof(struct note));


};