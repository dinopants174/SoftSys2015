#include <TinyWireS.h>

int LED = 1;
int count = 0;
int i;
byte recieve[2] = {};
void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  TinyWireS.begin(1); 
  // Attach a function to trigger when something is received.
}

//void loop() {
//  //If value received is 0 blink LED for 200 ms
//  if (TinyWireS.available()){
//    digitalWrite(LED, HIGH);
//    delay(1000);
//    digitalWrite(LED, LOW);
//    delay(1000);
//  }
//  else{
//    digitalWrite(LED, HIGH);
//    delay(5000);
//    digitalWrite(LED, LOW);
//    delay(5000);
//  }
//}


void loop(){
  byte byteRcvd = 0;
  if (TinyWireS.available() && count <= 2){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    recieve[count] = byteRcvd;
    count++;
  }
  
  if (count >= 2){
    for (i=0; i<=1; i++){
      Blink(LED, recieve[i]);
      delay(2000);
    }
  }
}


void Blink(int led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (250);
    digitalWrite(led,LOW);
    delay (175);
  }
}
