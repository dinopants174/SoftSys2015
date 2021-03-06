#include <Wire.h>
#include <stdio.h> 
#include <stdlib.h> 

// whole system parameters 
#define DELAY 500 // standard delay time in Demo mode
#define REQUEST_SIZE 1 // number of request each time
#define ROUNDING 0.5 // used to round pow() which returns a float before casting to int

// merge sort parameters
#define ARRAY_SIZE 12 // merge sort size
#define COMPARE_NUM 2 // the number of arrays that we are comparing

// single merge sort parameters
#define SINGLE_SIZE 5 // single merge sort size
#define SINGLE_FIRST_ARRAY 3 // the size of fisrt array to be sorted

// mode encoding
#define DEMO 1 // indication of demo mode
#define OPCODE 2 // operation code

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

//initializaiton for the two matrices to be multiplied
float A[2][2];
float B[2][2];
byte matrix_input[16] = {};
float C[2][2];

// initialization of the array to be sorted
byte res[ARRAY_SIZE] = {1, 8, 253, 28, 17, 134, 58, 27, 65, 82, 102, 20}; 

// initialization of two sorted array to be single sorted by one slave
byte singleRes[SINGLE_SIZE] = {3, 67, 98, 85, 101};

/* 

setup phase

*/
void setup() {
  Serial.begin(9600);
  Wire.begin(); 

  setupMatrix(1, 2, 3, 4, A);
  setupMatrix(5, 6, 7, 8, B);
  MatrixArrayTask(A, B);

  level = 1;
  finished_transmit = false;
  finished_receive = false;
  delay(5000);
}

/* 

loop phase

*/
void loop() {
  if (OPCODE == 0) {
    singleMergeSortLoop();
  } else if (OPCODE == 1) {
    matrixLoop();
  } else if (OPCODE == 2) {
    mergeSortLoop();
  }      
}

/* 

singleMergeSortLoop() behaves as the 
backbone of a single merge sorting. 
This method get called when opcode is 
defined as 0 in the preprocessing phase.

*/

void singleMergeSortLoop() {
  if (!finished_transmit && !finished_receive) {
    // print out statement for demo only
    if (DEMO) {
      delay(DELAY);
      Serial.println("Starts transmitting in mode single mergesort ");
      PrintLine();
    }

    for (int i = 0; i < SINGLE_SIZE; i++) {
      if (DEMO) Serial.println("Transmitting slave 1");

      Wire.beginTransmission(SLAVEONE); // transmit to slave address 0XB

      if (i == 0) {
        Wire.write(OPCODE+2);
        Wire.write(SINGLE_FIRST_ARRAY);
      }   

      Wire.write(singleRes[i]);
      Wire.endTransmission();
    }


    // indicates transmition is finished
    finished_transmit = true;

    // print out statement for demo only
    if (DEMO) {
      Serial.println("Transmitting finished");
      PrintLine();
      delay(DELAY);
    }
  }

  if (finished_transmit && !finished_receive) {
    int nodeAddress = SLAVEONE;
    if (DEMO) PrintRecSlave(nodeAddress); // print out statement for demo only
    for (int i = 0; i < SINGLE_SIZE; i++) {
      //
      if (Wire.requestFrom(nodeAddress, REQUEST_SIZE) == REQUEST_SIZE) {  
        singleRes[i] = Wire.read();
        if (DEMO) Serial.println(singleRes[i]);
      }
    }

    // indicates transmition is finished
    finished_receive = true;
    
    // print out statement for demo only
    if (DEMO) {
      Serial.println("Receiving finished");
      PrintLine();
      delay(DELAY);
    } 
  }

  // reset transmission and receiving values
  finished_transmit = false;
  finished_receive = false;
}

/* 

matrixLoop() behaves as the 
backbone of a matrix multiplication. 
This method get called when opcode is 
defined as 1 in the preprocessing phase.

*/

void matrixLoop() {
  if (!finished_transmit && !finished_receive) {
    // print out statement for demo only
    if (DEMO) {
      delay(DELAY);
      Serial.println("Starts transmitting in mode matrix multiplication ");
      PrintLine();
    }
    
    for (int i=SLAVEONE; i<SLAVEFIVE; i++){
      Wire.beginTransmission(i); // transmit to slave address 16
      Wire.write(OPCODE);
      for (int j=0; j<4; j++){
        Wire.write(matrix_input[j + (i - SLAVEONE)*4]);
      }
      Wire.endTransmission(); 
    }
    // indicates transmition is finished
    finished_transmit = true;

    // print out statement for demo only
    if (DEMO) {
      Serial.println("Transmitting finished");
      PrintLine();
      delay(DELAY);
    }
  }

  if (finished_transmit && !finished_receive) {
    byte temp[4] = {};
    for (int i=SLAVEONE; i<SLAVEFIVE; i++){
        if (Wire.requestFrom(i, REQUEST_SIZE) == REQUEST_SIZE) {
         temp[i - SLAVEONE] = Wire.read();
          Serial.print("Slave address ");
          Serial.println(i);
          Serial.println(temp[i-SLAVEONE]);      
        }
    }
    setupMatrix(temp[0], temp[1], temp[2], temp[3], C);
    
    // indicates transmition is finished
    finished_receive = true;
    
    // print out statement for demo only
    if (DEMO) {
      Serial.println("Receiving finished");
      PrintLine();
      delay(DELAY);
    } 

  // reset transmission and receiving values
  finished_transmit = false;
  finished_receive = false;
  }

}


/* 

mergeSortLoop() behaves as the backbone
of merge sorting. This method get called 
when opcode is defined as 2 in the 
preprocessing phase.

*/

void mergeSortLoop() {
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
      PrintLine();
      delay(DELAY);
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
      Serial.println("Receiving finished");
      PrintLine();
      delay(DELAY);
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
      Wire.write(OPCODE);
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
      Wire.write(OPCODE);
      Wire.write(byte(level));
    }   

    Wire.write(res[i]);
    Wire.endTransmission();
  }
}

/*

DemoTransmit() takes the current level and
number of slaves to perform a single transmission
on a single slave

*/

void DemoTransmit(int level, int slaveNum) {
  for (int i = (slaveNum - 1) * level * COMPARE_NUM; i < slaveNum * level * COMPARE_NUM; i++) {

    if (DEMO) {
      Serial.print("Transmitting slave ");
      Serial.println(10 + slaveNum);
    }

    Wire.beginTransmission(SLAVEONE + slaveNum - 1); // transmit to slave address 16

    if (i == (slaveNum - 1) * level * COMPARE_NUM) {
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

void setupMatrix(int a, int b, int c, int d, float M[2][2]) {
  M[0][0] = a;
  M[0][1] = b;
  M[1][0] = c;
  M[1][1] = d;
}

//function here to populate byte arrays
void MatrixArrayTask(float A[2][2], float B[2][2]) {
  byte a = A[0][0];
  byte b = A[0][1];
  byte c = A[1][0];
  byte d = A[1][1];
  
  byte e = B[0][0];
  byte f = B[0][1];
  byte g = B[1][0];
  byte h = B[1][1];
  
  matrix_input[0] = a;
  matrix_input[1] = e;
  matrix_input[2] = b;
  matrix_input[3] = g;
  matrix_input[4] = a;
  matrix_input[5] = f;
  matrix_input[6] = b;
  matrix_input[7] = h;
  matrix_input[8] = c;
  matrix_input[9] = e;
  matrix_input[10] = d;
  matrix_input[11] = g;
  matrix_input[12] = c;
  matrix_input[13] = f;
  matrix_input[14] = d;
  matrix_input[15] = h;
} 
