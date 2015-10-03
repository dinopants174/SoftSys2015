#include <stdio.h>

typedf struct { 
	float tank_capacity;
	int tank_psi;
	const char *suit_material; 
}kit;

typedef struct scuba { 
	const char *name;
	equipment kit; 
} diver;

void badge(diver d) {
	printf("Name: %s Tank: %2.2f(%i) Suit: %s\n",
	d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

int main() {
	badge(randy);
return 0;
}