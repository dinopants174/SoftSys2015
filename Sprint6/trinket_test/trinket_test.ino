#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 

int level;
bool finished_transmit;
bool finished_receive;
byte array[12];
byte res[12];

void setup() {
	Serial.begin(9600);
	Wire.begin(); 
	level = 1;
	finished_transmit = false;
	finished_receive = false;

	array = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20};
	res = array;
}

void loop() {
	if (!finished_transmit && !finished_receive){
		switch (level) {
			case 1:
				TransmitL1();
			case 2:
				TransmitL2();
			case 3:
				TransmitL3();
			case 4: 
				TransmitL4();
		}
		
		finished_transmit = true;
		delay(1000);
	}

	if (finished_transmit && !finished_receive){
		switch (level) {
			case 1:
				ReceiveL1();
				level = 2;
			case 2:
				ReceiveL2();
				level = 3;
			case 3:
				ReceiveL3();
				level = 4;
			case 4: 
				ReceiveL4();
				level = 1;
		}   

		finished_receive = true;
		delay(1000);
	}
	
	if (finished_transmit && finished_receive && level == 1){
		PrintList(&res[0], 12)
	}
}

void TransmitL1 () {
	Serial.println("*************************");   
	Serial.println("I am finished transmitting");
	for (int i = 1; i <= 6; i++) {
		SingleTransmit(1, i);       
	}
	Serial.println("*************************");      
}

void TransmitL2 () {
	Serial.println("*************************");   
	Serial.println("I am finished transmitting");
	for (int i = 1; i <= 3; i++) {
		SingleTransmit(2, i);       
	}
	Serial.println("*************************");      
}

void TransmitL3 () {
	Serial.println("*************************");   
	Serial.println("I am finished transmitting");
	SingleTransmit(4, i);       
	Serial.println("*************************");      
}

void TransmitL4 () {
	Serial.println("*************************");   
	Serial.println("I am finished transmitting");
	for (int i = 0; i < 12; i++) {
		Serial.println("Transmitting now slave %d", 1);
		Wire.beginTransmission(0xB); // transmit to slave address 16
		Serial.println(res[i]);
		if (i == 0) {
			Wire.write(8);
		}
		Wire.write(res[i]);
		Wire.endTransmission();
	}
	Serial.println("*************************");      
}

void SingleTransmit(int level, int slaveNum) {
	for (int i = (slaveNum - 1) * level * 2; i < slaveNum * level * 2; i++) {
		Serial.println("Transmitting now slave %d", slaveNum);
		Wire.beginTransmission(0xB + slaveNum - 1); // transmit to slave address 16
		Serial.println(res[i]);
		if (i == (slaveNum - 1) * level * 2) {
			Wire.write(byte(level));
		}		
		Wire.write(res[i]);
		Wire.endTransmission();
	}
}

void ReceiveL1() {
	for (int nodeAddress = 0xB; nodeAddress <= 0x10; nodeAddress++) { 
		Serial.println("*************From slave %d************", nodeAddress);      
		for (int i = 0; i < 2; i++) {
			if (Wire.requestFrom(nodeAddress, 1) == 1) {  
				res[(nodeAddress - 0xB) * 2 + i] = Wire.read();
				Serial.println(res[(nodeAddress - 0xB) * 2 + i]);
			}
		}
		Serial.println("**************************************************");      
	}
}

void ReceiveL2() {
	for (int nodeAddress = 0xB; nodeAddress <= 0xD; nodeAddress++) { 
		Serial.println("*************From slave %d************", nodeAddress);      
		for (int i = 0; i < 4; i++) {
			if (Wire.requestFrom(nodeAddress, 1) == 1) {  
				res[(nodeAddress - 0xB) * 4 + i] = Wire.read();
				Serial.println(res[(nodeAddress - 0xB) * 4 + i]);
			}
		}
		Serial.println("**************************************************");      
	}
}

void ReceiveL3() {
	Serial.println("*************From slave %d************", 1);      
	for (int i = 0; i < 8; i++) {
		if (Wire.requestFrom(0xB, 1) == 1) {  
			res[i] = Wire.read();
			Serial.println(res[i]);
		}
	}
	Serial.println("**************************************************");      
}

void ReceiveL4() {
	Serial.println("*************From slave %d************", 1);      
	for (int i = 0; i < 12; i++) {
		if (Wire.requestFrom(0xB, 1) == 1) {  
			res[i] = Wire.read();
			Serial.println(res[i]);
		}
	}
	Serial.println("**************************************************");      
}

void PrintList (int* A, int size_A)
{
	int i = 0;
 	while (i < size_A)
 	{
	printf("%d\n",A[i]);
	i++;
	}
}