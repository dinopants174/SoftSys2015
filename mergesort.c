#include <stdio.h> 
#include <stdlib.h> 

// void PrintList (int* A)
// {
// 	int i=Length(A);
//  	while (i<0)
//  	{
// 	printf("%d\n",A[i]);
// 	i--;
// 	}
// }

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



int* MergeSort (int* A, int A_size, int* B,  int B_size)
{

int size_C = A_size + B_size;

int* C; 

int size_A = A_size;
int size_B = B_size;

int sep = Separate(A, A_size, B, B_size, C);

	if (sep == 0) {

		int i =0; 
		while (i < size_C)
		{
			int C_size = i; 
			if (size_A == 0) {AddAndPop(C,&C_size,&B,&size_B);}
			else if (size_B == 0) {AddAndPop(C,&C_size,&A,&size_B);}
			else if (A[0]>B[0]) {AddAndPop(C,&C_size,&B,&size_B);}
			else if (B[0]>A[0]) {AddAndPop(C,&C_size,&B,&size_A);}
			else {AddAndPop(C,&C_size,&A,&size_A);}
			i++;
		}
	}

return C;

}


void main() {
	int A[2]={1,2}; const int A_size=2; int* ptrA=&A[0];
	int B[2]={3,4}; const int B_size=2; int* ptrB=&B[0];
	int C[2]={3,4}; const int C_size=2; int* ptrC=&C[0];
	int D[2]={5,7}; const int D_size=2; int* ptrD=&D[0];
	int E[2]={3,6}; const int E_size=2; int* ptrE=&E[0];
	int F[2]={9,11};const int F_size=2; int* ptrF=&F[0];

	int* AB=MergeSort(ptrA,A_size,ptrB,B_size); const int AB_size=A_size+B_size;
	// int* CD=MergeSort(C,D,C_size,D_size); CD_size=Length(CD);
	// int* EF=MergeSort(E,F,E_size,F_size); EF_size=Length(EF);
	
	// int* ABCD=MergeSort(AB,CD,AB_size,CD_size); ABCD_size=Length(ABCD);

	// int* ABCDEF=MergeSort(ABCD,EF,ABCD_size,EF_size);

	// PrintList(AB);
	printf("%d\n", AB[0]);

	// int size_A = 4;
	// int A[4] = {1,2,3,4}; int* ptrA=&A[0];
	// int C[1] = {};

	// AddAndPop(C, 1, &&A, &size_A);
	


}



// #include <stdio.h>

// int separate(int* A, int size_A_bef, int* B, int size_B_bef, int* C, int size_C_bef);
// int addAndPop(int* add, int size_add, int* pop, int* size_pop);

// int main() {
// 	int size_A = 4;
// 	int A[4] = {1,2,3,4};
// 	int C[1] = {};

// 	addAndPop(C, 1, A, &size_A);
// 	return 0;
// }

// int separate(int* A, int size_A_bef, int* B, int size_B_bef, int* C, int size_C_bef) {
// 	int size_A = size_A_bef;
// 	int size_B = size_B_bef;
// 	int size_C = size_C_bef;

// 	int preA = A[size_A - 1] <= B[0];
// 	int preB = B[size_B - 1] <= A[0];

// 	if (preA) {

// 		while (size_A > 0) {
// 			addAndPop(C, size_C, A, &size_A);
// 		}

// 		while (size_B > 0) {
// 			addAndPop(C, size_C, B, &size_B);
// 		}

// 	} else if (preB) {

// 		while (size_B > 0) {
// 			addAndPop(C, size_C, B, &size_B);
// 		}

// 		while (size_A > 0) {
// 			addAndPop(C, size_C, A, &size_A);
// 		}

// 	}

// 	return (preA || preB);
// }

// int addAndPop(int* add, int size_add, int* pop, int* size_pop) {
// 	add[size_add] = pop[0];
// 	if (*size_pop > 0) {		
// 		pop += sizeof(int);
// 		*size_pop--;
// 	} 
// }