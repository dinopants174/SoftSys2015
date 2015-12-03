#include <Wire.h>
#define I2C_SLAVE_ADDR  0xE            // i2c slave address (38)

int i;
int nodeAddress;
byte arr1[4] = {};
byte arr2[4] = {};
byte arr3[4] = {};
byte arr4[4] = {};
byte res[4] = {};
//put matrices here
float A[2][2];
float B[2][2];
byte byteReceived;
bool finished_transmit = false;

void setup() {
  Serial.begin(9600);
  setupMatrix(1, 2, 3, 4, A);
  setupMatrix(5, 6, 7, 8, B);
  MatrixArrayTask(A, B);
  Wire.begin(); 
}

void loop() {
  if (!finished_transmit){
    Serial.println("*************************");      
    for (i=0; i<4; i++){
      Serial.println("Transmitting now slave 1");
      Wire.beginTransmission(0xB); // transmit to device #9
      Serial.println(arr1[i]);
      Wire.write(arr1[i]);
      Wire.endTransmission();
    }
    for (i=0; i<4; i++){
      Serial.println("Transmitting now slave 2");
      Wire.beginTransmission(0xB + 0x1); // transmit to device #9
      Serial.println(arr2[i]);
      Wire.write(arr2[i]);
      Wire.endTransmission();
    }
    for (i=0; i<4; i++){
      Serial.println("Transmitting now slave 3");
      Wire.beginTransmission(0xB + 0x2); // transmit to device #9
      Serial.println(arr3[i]);
      Wire.write(arr3[i]);
      Wire.endTransmission();
    }
    for (i=0; i<4; i++){
      Serial.println("Transmitting now slave 4");
      Wire.beginTransmission(0xB + 0x3); // transmit to device #9
      Serial.println(arr4[i]);
      Wire.write(arr4[i]);
      Wire.endTransmission();
    }
    Serial.println("I am finished transmitting");
    Serial.println("*************************");      
     finished_transmit = true;
     delay(1000);
 }
  
  if (finished_transmit){
    for (int nodeAddress = 0xB; nodeAddress <= 0xE; nodeAddress++) { // we are starting from Node address 2
    Wire.requestFrom(nodeAddress, 1);    // request data from node#
    if(Wire.available() == 1) {  // if data size is avaliable from nodes
      byteReceived = Wire.read();
      Serial.print("Address ");
      Serial.println(nodeAddress);
      res[nodeAddress - 0xB] = byteReceived;
      Serial.println(res[nodeAddress - 0xB]);
      Serial.println("*************************");      
      }
    }
    delay(1000);
  }
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
  
  arr1[0] = a;
  arr1[1] = e;
  arr1[2] = b;
  arr1[3] = g;
  arr2[0] = a;
  arr2[1] = f;
  arr2[2] = b;
  arr2[3] = h;
  arr3[0] = c;
  arr3[1] = e;
  arr3[2] = d;
  arr3[3] = g;
  arr4[0] = c;
  arr4[1] = f;
  arr4[2] = d;
  arr4[3] = h;
}
