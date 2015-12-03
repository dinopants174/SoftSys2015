#include <TinyWireS.h>
#define I2C_SLAVE_ADDR  0xE           // i2c slave address (38)


int count = 0;
int i;
byte recieve[4] = {};
byte res = 0;
bool finished_receive = false;
bool finished_add = false;

void setup() {  
  TinyWireS.begin(I2C_SLAVE_ADDR); 
  TinyWireS.onRequest(requestEvent);
}

void loop(){
  byte byteRcvd = 0;
  if (TinyWireS.available() && !finished_receive && !finished_add){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    recieve[count] = byteRcvd;
    count++;
    if (count > 3){
      finished_receive = true;
    }
  }
  
  if (finished_receive && !finished_add){
    compute(recieve);
    }
    
  if (finished_receive && finished_add){
    }
}


void compute(byte val[4]){
  res = val[0]*val[1] + val[2]*val[3];
  finished_add = true;
}

void add(byte val[4]){
  for (byte i=0; i < 4; i++){  //i<x matches val[x]
    res += val[i];
  }
  finished_add = true;
}

void Blink(int led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (500);
    digitalWrite(led,LOW);
    delay (500);
  }
}

void requestEvent(){
  TinyWireS.send(res);
}
