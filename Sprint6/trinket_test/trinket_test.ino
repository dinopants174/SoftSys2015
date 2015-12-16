#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 
 
#define ARRAY_SIZE 12 // merge sort size
#define DELAY 2000 // standard delay time in Demo mode
#define DEMO 1 // indication of Demo mode
#define COMPARE_NUM 2 // the number of arrays that we are comparing
#define REQUEST_SIZE 1 // number of request each time
#define ROUNDING 0.5 // used to round pow() which returns a float before casting to int

// slave encoding
#define SLAVEONE 0XB
#define SLAVETWO 0XC
#define SLAVETHREE 0XD
#define SLAVEFOUR 0XE
#define SLAVEFIVE 0XF
#define SLAVESIX 0X10

int level; // indicates the level of current phase 
bool finished_transmit; // indicates state of transmitting
bool finished_receive; // indicates state of receiving
// initialization of the array to be sorted
byte res[ARRAY_SIZE] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20}; 

/* 

setup phase

*/
void setup() {
  Serial.begin(9600);
  Wire.begin(); 

  level = 1;
  finished_transmit = false;
  finished_receive = false;
  delay(5000);
}

/* 

loop phase

*/
void loop() {
  if (!finished_transmit && !finished_receive){
    // print out statement for demo only
    if (DEMO) {
      delay(DELAY);
      Serial.print("Current level: ");
      Serial.println(level);
      PrintLine();
    }

    // a nested level choosing statement
    if (level == 1) {
        Transmit(6, level);
      } else if (level == 2) {
        Transmit(3, level);
      } else if (level == 3) {
        Transmit(1, level);
      } else if (level == 4) {
        TransmitFinal();
      }

    // indicates transmition is finished
    finished_transmit = true;

    // print out statement for demo only
    if (DEMO) {
      Serial.println("Transmitting finished");
      delay(DELAY);
      PrintLine();
    }
  }

  if (finished_transmit && !finished_receive){

    // print out statement for demo only
    if (DEMO) {
      delay(DELAY);
      PrintLine();
      Serial.println("Receiving starts");
    }

    // a nested level choosing statement
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

    // indicates transmition is finished
    finished_receive = true;
    
    // print out statement for demo only
    if (DEMO) {
      PrintLine();
      Serial.println("Receiving finished");
      PrintLine();
      delay(1000);
    } 
  }
  
  // reset transmission and receiving values
  finished_transmit = false;
  finished_receive = false;      
}

/*

Transmit() takes the slave number and current value
to perform transmitting.

*/
void Transmit (int slaveNum, int level) {
  int rep = pow(COMPARE_NUM, level - 1) + ROUNDING; // repeat number for each slave
  // iterate through the slaves to perform single transmitting
  for (int i = 1; i <= slaveNum; i++) { 
    SingleTransmit(rep, i);       
  }
}

/*

TransmitFinal() transimits the final level in the 
mergesort phase. 

*/

void TransmitFinal () {
  for (int i = 0; i < ARRAY_SIZE; i++) { // transmit all the element in the array

    // print out statement for demo only
    if (DEMO) {
      Serial.println("Transmitting slave 11");
    }

    Wire.beginTransmission(SLAVEONE); // transmit to slave address 0XB

    // write the size of array 1
    if (i == 0) {
      Wire.write(2);
      Wire.write(8);
    }

    Wire.write(res[i]); // perform transmitting
    Wire.endTransmission(); // end transmitting
  }
}

/*

SingleTransmit() takes the current level and
number of slaves to perform a single transmission
on a single slave

*/

void SingleTransmit(int level, int slaveNum) {
  for (int i = (slaveNum - 1) * level * COMPARE_NUM; i < slaveNum * level * COMPARE_NUM; i++) {

    if (DEMO) {
      Serial.print("Transmitting slave ");
      Serial.println(10 + slaveNum);
    }

    Wire.beginTransmission(SLAVEONE + slaveNum - 1); // transmit to slave address 16

    if (i == (slaveNum - 1) * level * COMPARE_NUM) {
      Wire.write(2);
      Wire.write(byte(level));
    }   

    Wire.write(res[i]);
    Wire.endTransmission();
  }
}

/*

Receive() takes the slave number and current value
to perform receiving.

*/

void Receive(int slaveNum, int level) {
  // iterates through the slaves as specified by slave number
  for (int nodeAddress = SLAVEONE; nodeAddress <= slaveNum; nodeAddress++) { 
    if (DEMO) PrintRecSlave(nodeAddress); // print out statement for demo only
    int rep = pow(COMPARE_NUM, level) + ROUNDING; // get the repeat number
    Serial.print("Rep value: ");
    Serial.println(rep);
    for (int i = 0; i < rep; i++) {
      //
      if (Wire.requestFrom(nodeAddress, REQUEST_SIZE) == REQUEST_SIZE) {  
        res[(nodeAddress - SLAVEONE) * rep + i] = Wire.read();
        if (DEMO) Serial.println(res[(nodeAddress - SLAVEONE) * rep + i]);
      }
    }
  }
}

/*

ReceiveFinal() receives the final level in the 
mergesort phase. 

*/

void ReceiveFinal() {
  if (DEMO) PrintRecSlave(SLAVEONE); // prints out statement for demo only
  for (int i = 0; i < ARRAY_SIZE; i++) { // iterates through all the element in the array
    //receives a byte at a time
    if (Wire.requestFrom(SLAVEONE, REQUEST_SIZE) == REQUEST_SIZE) {  
      res[i] = Wire.read();
      if (DEMO) Serial.println(res[i]); // print out statement for demo only
    }
  }
}

/*

PrintList() get the size of the array
and a pointer to the array to print
out all the elements inside the array

*/

void PrintList (byte* A, int size_A) {
  int i = 0;
  while (i < size_A)
  {
    Serial.println(A[i]);
    i++;
  }
}

/*

PrintRecSlave() get the address of the slave 
and prints out the byte each time master
receives it

*/

void PrintRecSlave(int nodeAddress) {
  Serial.print("Receive from slave "); 
  Serial.println(nodeAddress); 
}

/*

PrintLine() prints out a line of '*'
to make the print statement more
distinguishing 

*/

void PrintLine() {
  Serial.println("********************");
}
