#include <stdio.h> 
#include <stdlib.h> 

void PrintList (int* A, int size_A)
{
	int i = 0;
 	while (i < size_A)
 	{
	printf("%d\n",A[i]);
	i++;
	}
}

void AddAndPop (int* add, int* size_add, int** pop, int* size_pop) {
	add[*size_add] = (*pop)[0];
	*size_add += 1;

	if (*size_pop > 0) {		
		*pop += 1;
		*size_pop -= 1;
	} 
}

int Separate(int* A, int size_A_bef, int* B, int size_B_bef, int* C) {
	int size_A = size_A_bef;
	int size_B = size_B_bef;
	int size_C = 0;

	int preA = A[size_A - 1] <= B[0];
	int preB = B[size_B - 1] <= A[0];

	if (preA) {

		while (size_A > 0) {
			AddAndPop(C, &size_C, &A, &size_A);
		}

		while (size_B > 0) {
			AddAndPop(C, &size_C, &B, &size_B);
		}

	} else if (preB) {

		while (size_B > 0) {
			AddAndPop(C, &size_C, &B, &size_B);
		}

		while (size_A > 0) {
			AddAndPop(C, &size_C, &A, &size_A);
		}

	}

	return (preA || preB);
}



void MergeSort (int* A, int A_size, int* B, int B_size, int* C)
{

int size_C = A_size + B_size;

int size_A = A_size;
int size_B = B_size;

int sep = Separate(A, A_size, B, B_size, C);

// printf("%d\n", sep);
	if (sep == 0) {

		int i =0; 
		while (i < size_C)
		{
			int C_size = i; 

			if (size_A == 0) {
				AddAndPop(C, &C_size, &B, &size_B);
			} else if (size_B == 0) {
				AddAndPop(C, &C_size, &A, &size_A);
			} else if (A[0]>B[0]) {
				AddAndPop(C, &C_size, &B, &size_B);
			} else if (B[0]>=A[0]) {
				AddAndPop(C, &C_size, &A, &size_A);
			} 

			i++;
		}
	}
}


void main() {

	int A[4]={4,5,9,10}; int A_size=4; int* ptrA=&A[0];
	int B[3]={3,4,7}; int B_size=3; int* ptrB=&B[0];

	int AB_size=A_size+B_size;

	int* AB = (int*)malloc(sizeof(int)*AB_size);
	MergeSort(ptrA,A_size,ptrB,B_size,AB); 

	PrintList(AB, AB_size);
}


