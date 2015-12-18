#include <Wire.h>

int x = 0;
int i = 0;
String data = "[2,4;6,8]";

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Wire.begin(); 
}

void loop() {
  Wire.beginTransmission(9); // transmit to device #9
  for(i=0; i<9; i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();    // stop transmitting

  delay(500);
}

