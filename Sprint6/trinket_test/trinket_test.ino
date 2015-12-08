#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 

int i;
int nodeAddress;
byte array[12] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20};
byte res[6][2] = {{0, 0}, {0, 0}, {0, 0}, {0,0}, {0,0}, {0,0}};
byte C[4] = {};
byte D[4] = {};
byte E[4] = {};
byte F[8] = {};
byte G[12] = {};
byte byteReceived1;
byte byteReceived2;
bool finished_transmit = false;
bool finished_receive = false;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
}

void loop() {
  if (!finished_transmit && !finished_receive){
    Serial.println("*************************");      
    for (i=0; i<2; i++){
      Serial.println("Transmitting now slave 1");
      Wire.beginTransmission(0xB); // transmit to slave address 11
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    for (i=2; i<4; i++){
      Serial.println("Transmitting now slave 2");
      Wire.beginTransmission(0xB + 0x1); // transmit to slave address 12
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    for (i=4; i<6; i++){
      Serial.println("Transmitting now slave 3");
      Wire.beginTransmission(0xB + 0x2); // transmit to slave address 13
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    for (i=6; i<8; i++){
      Serial.println("Transmitting now slave 4");
      Wire.beginTransmission(0xB + 0x3); // transmit to slave address 14
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    for (i=8; i<10; i++){
      Serial.println("Transmitting now slave 5");
      Wire.beginTransmission(0xB + 0x4); // transmit to slave address 15
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    for (i=10; i<12; i++){
      Serial.println("Transmitting now slave 6");
      Wire.beginTransmission(0xB + 0x5); // transmit to slave address 16
      Serial.println(array[i]);
      Wire.write(array[i]);
      Wire.endTransmission();
    }
    
    Serial.println("I am finished transmitting");
    Serial.println("*************************");      
    finished_transmit = true;
    delay(1000);
 }
  
  if (finished_transmit && !finished_receive){
    for (int nodeAddress = 0xB; nodeAddress <= 0x10; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, 2);    // request data from node#
    if(Wire.available() == 2) {  // if data size is avaliable from nodes
      byteReceived1 = Wire.read();
      byteReceived2 = Wire.read(); 
      Serial.print("Address ");
      Serial.println(nodeAddress);
      res[nodeAddress - 0xB][0] = byteReceived1;
      res[nodeAddress - 0xB][1] = byteReceived2;
//      res[nodeAddress - 0xB] = byteReceived1;
//      res[nodeAddress - 0xB + 0x1] = byteReceived2;
      Serial.println(res[nodeAddress - 0xB][0]);
      Serial.println(res[nodeAddress - 0xB][1]);
      Serial.println("*************************");      
      }
    }
    delay(1000);
    finished_receive = true;
  }
  
  if (finished_transmit && finished_receive){
    MergeSort(&res[0][0], 2, &res[1][0], 2, &C[0]);
    MergeSort(&res[2][0], 2, &res[3][0], 2, &D[0]);
    MergeSort(&res[4][0], 2, &res[5][0], 2, &E[0]);
    MergeSort(&C[0], 4, &D[0], 4, &F[0]);
    MergeSort(&F[0], 8, &E[0], 4, &G[0]);
    Serial.println("***********************");
    PrintList(&G[0], 12);
  }
}


void PrintList (byte* A, int size_A)
{
	int i = 0;
 	while (i < size_A)
 	{
	Serial.println(A[i]);
	i++;
	}
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
