#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 

int level;
bool finished_transmit;
bool finished_receive;
byte array[12] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20};
byte res[12] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20};

void setup() {
	Serial.begin(9600);
	Wire.begin(); 
	level = 1;
	finished_transmit = false;
	finished_receive = false;

}

void loop() {
	if (!finished_transmit && !finished_receive){
                delay(5000);
                Serial.println(level);
    		if (level == 1) {
                    TransmitL1();
                } else if (level == 2) {
                    TransmitL2();
                } else if (level == 3) {
                    TransmitL3();
                } else if (level == 4) {
                    TransmitL4();
                }
    		
    		finished_transmit = true;
                Serial.println("I have transmitted a level");
    		delay(1000);
	}

	if (finished_transmit && !finished_receive){
  
                if (level == 1) {
                    ReceiveL1();
                    level = 2;
                } 
                else if (level == 2) {
                    ReceiveL2();
                    level = 3;
                } else if (level == 3) {
                    ReceiveL3();
                    level = 4;
                } else if (level == 4) {
                    ReceiveL4();
                    level = 1;
                }  
                Serial.println("in the phase of receive");
		finished_receive = true;
		delay(1000);
	}
	
	if (finished_transmit && finished_receive && level == 1){
		PrintList(&res[0], 12);
	}
        finished_transmit = false;
        finished_receive = false;        
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
	SingleTransmit(4, 1);       
	Serial.println("*************************");      
}

void TransmitL4 () {
	Serial.println("*************************");   
	Serial.println("I am finished transmitting");
	for (int i = 0; i < 12; i++) {
                Serial.print("Transmitting now slave ");
                Serial.println(1);
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
		Serial.print("Transmitting now slave ");
                Serial.println(slaveNum);
		Wire.beginTransmission(0xB + slaveNum - 1); // transmit to slave address 16
		if (i == (slaveNum - 1) * level * 2) {
			Wire.write(byte(level));
		}		
		Wire.write(res[i]);
                Serial.println(res[i]);
		Wire.endTransmission();
	}
}

void ReceiveL1() {
	for (int nodeAddress = 0xB; nodeAddress <= 0x10; nodeAddress++) { 
                Serial.print("*************From slave************");
                Serial.println(nodeAddress);    
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
		Serial.print("*************From slave************");
                Serial.println(nodeAddress);      
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
	Serial.print("*************From slave************");
        Serial.println(1);       
	for (int i = 0; i < 8; i++) {
		if (Wire.requestFrom(0xB, 1) == 1) {  
			res[i] = Wire.read();
			Serial.println(res[i]);
		}
	}
	Serial.println("**************************************************");      
}

void ReceiveL4() {
	Serial.print("*************From slave************");
        Serial.println(1);      
	for (int i = 0; i < 12; i++) {
		if (Wire.requestFrom(0xB, 1) == 1) {  
			res[i] = Wire.read();
			Serial.println(res[i]);
		}
	}
	Serial.println("**************************************************");      
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
