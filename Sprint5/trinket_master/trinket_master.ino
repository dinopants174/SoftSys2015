#include <Wire.h>

int x = 3;
int i;
byte transmit[2] = {1,5};
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
}
void loop() {
  for  (i=0; i<2; i++){
    Wire.beginTransmission(1); // transmit to device #9
    Wire.write(transmit[i]);
    Wire.endTransmission();
  }

  
//  Wire.beginTransmission(1); // transmit to device #1
//  Wire.write(x);              // sends x 
//  Wire.endTransmission();    // stop transmitting
//  delay(5000);
//  x++; // Increment x
//  if (x > 5) x = 0; // `reset x once it gets 6
}
