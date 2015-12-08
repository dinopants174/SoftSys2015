#include <TinyWireS.h>
#define I2C_SLAVE_ADDR  0xB           // i2c slave address (38)


int count = 0;
int i;
byte recieve[2] = {};
byte arr1[1] = {};
byte arr2[1] = {};
byte res = 0;
bool finished_receive = false;
bool finished_compute = false;

void setup() {  
  TinyWireS.begin(I2C_SLAVE_ADDR); 
  TinyWireS.onRequest(requestEvent);
}

void loop(){
  byte byteRcvd = 0;
  if (TinyWireS.available() && !finished_receive && !finished_compute){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    recieve[count] = byteRcvd;
    count++;
    if (count > 1){
      finished_receive = true;
    }
  }
  
  if (finished_receive && !finished_compute){
    arr1[0] = recieve[0];
    arr2[0] = recieve[1];
    MergeSort(&arr1[0], 1, &arr2[0], 1, &recieve[0]);
    finished_compute = true;
    }
    
  if (finished_receive && finished_compute){
    }
}


void compute(byte val[4]){
  res = val[0]*val[1] + val[2]*val[3];
}

void add(byte val[4]){
  for (byte i=0; i < 4; i++){  //i<x matches val[x]
    res += val[i];
  }
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
  for (i=0; i<2; i++){
    TinyWireS.send(recieve[i]);
  }
//  TinyWireS.send(res);
  delay(5000);
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

