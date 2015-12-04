#include <stdio.h>

int separate(int* A, int size_A_bef, int* B, int size_B_bef, int* C, int size_C_bef);
void addAndPop(int* add, int size_add, int** pop, int* size_pop);

void foo(void* ptr) {}

int main() {
	int size_A = 4;
	int A[4] = {5,6,7,8};
	int* ptrA = &A[0];

	int size_B = 4;
	int B[4] = {1,2,3,4};
	int* ptrB = &B[0];

	int C[8] = {};
	int* ptrC = &C[0];

	separate(ptrA, size_A, ptrB, size_B, ptrC, 1);
	return 0;
}

int separate(int* A, int size_A_bef, int* B, int size_B_bef, int* C, int size_C_bef) {
	int size_A = size_A_bef;
	int size_B = size_B_bef;
	int size_C = size_C_bef;

	int preA = A[size_A - 1] <= B[0];
	int preB = B[size_B - 1] <= A[0];

	if (preA) {

		while (size_A > 0) {
			addAndPop(C, size_C, &A, &size_A);
		}

		while (size_B > 0) {
			addAndPop(C, size_C, &B, &size_B);
		}

	} else if (preB) {

		while (size_B > 0) {
			addAndPop(C, size_C, &B, &size_B);
		}

		while (size_A > 0) {
			addAndPop(C, size_C, &A, &size_A);
		}

	}

	return (preA || preB);
}

void addAndPop(int* add, int size_add, int** pop, int* size_pop) {
	add[size_add - 1] = (*pop)[0];
	if (*size_pop > 0) {
		*pop += 1;
		*size_pop -= 1;

	printf("%d\n", add[0]);
	} 
}

