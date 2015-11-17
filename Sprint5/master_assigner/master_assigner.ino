#include <Wire.h>

int x = 3;
int i;
byte arr1[4] = {1,5,2,7};
byte arr2[4] = {1,6,2,8};
byte arr3[4] = {3,5,4,7};
byte arr4[4] = {3,6,4,8};
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
}
void loop() {
  assign(arr1,arr2,arr3,arr4); 
  request();
  }
  
void assign(byte arr1[4], byte arr2[4], byte arr3[4]), byte arr4[4]{
    for (i=0; i<40; i++){
    Wire.beginTransmission(1);
    Wire.write(arr1[i%4]);
    Wire.endTransmission();
  }
    for (i=0; i<40; i++){
    Wire.beginTransmission(2);
    Wire.write(arr2[i%4]);
    Wire.endTransmission();
  }
    for (i=0; i<40; i++){
    Wire.beginTransmission(3);
    Wire.write(arr3[i%4]);
    Wire.endTransmission();
  }
    for (i=0; i<40; i++){
    Wire.beginTransmission(4);
    Wire.write(arr4[i%4]);
    Wire.endTransmission();
  }
}

int request(){
  int newm[2][2];
  int temp[4];
  Wire.requestFrom(1,1,false);
  while(Wire.available()) {
    temp[0] = Wire.read();
  }
  Wire.requestFrom(2,1,false);
  while(Wire.available()) {
    temp[1] = Wire.read();
  }
  Wire.requestFrom(3,1,false);
  while(Wire.available()) {
    temp[2] = Wire.read();
  }
  Wire.requestFrom(4,1,false);
  while(Wire.available()) {
    temp[3] = Wire.read();
  }
  newm[0][0] = temp[0];
  newm[0][1] = temp[1];
  newm[1][0] = temp[2];
  newm[1][1] = temp[3];
  return newm;
  
}
//  Wire.beginTransmission(1); // transmit to device #1
//  Wire.write(x);              // sends x 
//  Wire.endTransmission();    // stop transmitting
//  delay(5000);
//  x++; // Increment x
//  if (x > 5) x = 0; // `reset x once it gets 6
}
