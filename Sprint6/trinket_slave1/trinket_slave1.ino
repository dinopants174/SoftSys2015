#include <TinyWireS.h>
#define I2C_SLAVE_ADDR  0x10           // i2c slave address (38)
#define TWI_RX_BUFFER_SIZE ( 16 )

int count = 0;
int i;
int arr1_size;
int res_count = 0;
byte recieve_buffer[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte* arr1;
byte* arr2;
byte* arr3;

void setup() {  
  TinyWireS.begin(I2C_SLAVE_ADDR); 
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void loop(){
}

void Blink(int led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (500);
    digitalWrite(led,LOW);
    delay (500);
  }
}

void requestEvent(){
    TinyWireS.send(arr3[res_count]);
    recieve_buffer[res_count] = 0;
    res_count++;
    if (res_count > count-1){
        res_count = 0;
        count = 0;
        freeArray();
    }
}

void receiveEvent(uint8_t howMany)
{
    if (howMany < 1){
        // Sanity-check
        return;
    }
    if (howMany > TWI_RX_BUFFER_SIZE){
        // Also insane number
        return;
    }
    if (!howMany){
      return;
    }
    
    arr1_size = TinyWireS.receive();
    howMany--;
    
    while(howMany--){
      recieve_buffer[count] = TinyWireS.receive();
      count++;
    }
    createArray(arr1_size, count-arr1_size, count);
    for (i=0; i<arr1_size; i++){
      arr1[i] = recieve_buffer[i];
    }
    for (i=arr1_size; i<count; i++){
      arr2[i-arr1_size] = recieve_buffer[i];
    }
    MergeSort(arr1, arr1_size, arr2, count-arr1_size, arr3);
}


void AddAndPop (byte* add, int* size_add, byte** pop, int* size_pop) {
	add[*size_add] = (*pop)[0];
	*size_add += 1;

	if (*size_pop > 0) {		
		*pop += 1;
		*size_pop -= 1;
	} 
}

int Separate(byte* A, int size_A_bef, byte* B, int size_B_bef, byte* C) {
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



void MergeSort (byte* A, int A_size, byte* B, int B_size, byte* C)
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
			if (size_A == 0) {AddAndPop(C,&C_size,&B,&size_B);}
			else if (size_B == 0) {AddAndPop(C,&C_size,&A,&size_A);}
			else if (A[0]>B[0]) {AddAndPop(C,&C_size,&B,&size_B);}
			else if (B[0]>A[0]) {AddAndPop(C,&C_size,&A,&size_A);}
			else {AddAndPop(C,&C_size,&A,&size_A);}
			i++;
		}
	}
}

void createArray(int size_A, int size_B, int size_C) {
	arr1 = (byte*)malloc(sizeof(byte) * size_A);
	arr2 = (byte*)malloc(sizeof(byte) * size_B);
        arr3 = (byte*)malloc(sizeof(byte) * size_C);
}

void freeArray() {
	free(arr1);
	free(arr2);
        free(arr3);
}
