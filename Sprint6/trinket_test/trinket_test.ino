#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 

#define ARRAY_SIZE 12
#define DELAY 2000
#define DEMO 1
#define COMPARE_NUM 2
#define REQUEST_SIZE 1

#define SLAVEONE 0XB
#define SLAVETWO 0XC
#define SLAVETHREE 0XD
#define SLAVEFOUR 0XE
#define SLAVEFIVE 0XF
#define SLAVESIX 0X10

int level;
bool finished_transmit;
bool finished_receive;
byte res[ARRAY_SIZE] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20};

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  level = 1;
  finished_transmit = false;
  finished_receive = false;
}

void loop() {
  if (!finished_transmit && !finished_receive){

    if (DEMO) {
      delay(DELAY);
      Serial.print("Current level: ");
      Serial.println(level);
      PrintLine();
    }

    if (level == 1) {
        Transmit(6, level);
      } else if (level == 2) {
        Transmit(3, level);
      } else if (level == 3) {
        Transmit(1, level);
      } else if (level == 4) {
        TransmitFinal();
      }

    finished_transmit = true;

    if (DEMO) {
      Serial.println("Transmitting finished");
      delay(DELAY);
      PrintLine();
    }
  }

  if (finished_transmit && !finished_receive){

    if (DEMO) {
      delay(DELAY);
      PrintLine();
      Serial.println("Receiving starts");
    }

    if (level == 1) {
      Receive(SLAVESIX, level);
      level = 2;
    } else if (level == 2) {
      Receive(SLAVETHREE, level);
      level = 3;
    } else if (level == 3) {
      Receive(SLAVEONE, level);
      level = 4;
    } else if (level == 4) {
      ReceiveFinal();
      level = 1;
    } 

    finished_receive = true;
    
    if (DEMO) {
      PrintLine();
      Serial.println("Receiving finished");
      PrintLine();
      delay(1000);
    } 
  }
  
  if (finished_transmit && finished_receive && level == 1){
    PrintList(&res[0], 12);
  }

  finished_transmit = false;
  finished_receive = false;        
}

void Transmit (int slaveNum, int level) {
  int rep = pow(COMPARE_NUM, level - 1);
  for (int i = 1; i <= slaveNum; i++) {
    SingleTransmit(rep, i);       
  }
}

void TransmitFinal () {
  for (int i = 0; i < 12; i++) {

    if (DEMO) {
      Serial.print("Transmitting slave 1");
    }

    Wire.beginTransmission(SLAVEONE); // transmit to slave address 16
    if (DEMO) Serial.println(res[i]);

    if (i == 0) {
      Wire.write(8);
    }

    Wire.write(res[i]);
    Wire.endTransmission();
  }
}

void SingleTransmit(int level, int slaveNum) {
  for (int i = (slaveNum - 1) * level * COMPARE_NUM; i < slaveNum * level * COMPARE_NUM; i++) {

    if (DEMO) {
      Serial.print("Transmitting slave ");
      Serial.println(slaveNum);
    }

    Wire.beginTransmission(SLAVEONE + slaveNum - 1); // transmit to slave address 16

    if (i == (slaveNum - 1) * level * COMPARE_NUM) {
      Wire.write(byte(level));
    }   

    Wire.write(res[i]);
    Wire.endTransmission();
  }
}

void Receive(int slaveNum, level) {
  for (int nodeAddress = SLAVEONE; nodeAddress <= slaveNum; nodeAddress++) { 
    PrintRecSlave(nodeAddress);
    int rep = pow(COMPARE_NUM, level);
    for (int i = 0; i < rep; i++) {
      if (Wire.requestFrom(nodeAddress, REQUEST_SIZE) == REQUEST_SIZE) {  
        res[(nodeAddress - SLAVEONE) * rep + i] = Wire.read();
        if (DEMO) Serial.println(res[(nodeAddress - SLAVEONE) * rep + i]);
      }
    }
  }
}

void ReceiveFinal() {
  PrintRecSlave(SLAVEONE);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (Wire.requestFrom(SLAVEONE, REQUEST_SIZE) == REQUEST_SIZE) {  
      res[i] = Wire.read();
      if (DEMO) Serial.println(res[i]);
    }
  }
}

void PrintList (byte* A, int size_A) {
  int i = 0;
  while (i < size_A)
  {
    Serial.println(A[i]);
  i++;
  }
}

void PrintRecSlave(int nodeAddress) {
  Serial.print("Receive from slave "); 
  Serial.println(nodeAddress) 
}

void PrintLine() {
  Serial.println("********************");
}