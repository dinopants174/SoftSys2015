//Sine out w/ 40kHz sampling rate
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Audio-Output/
//Sept 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/
//Sound output options
byte sine[] = { 98, 104, 110, 116, 122, 128, 133, 139, 144, 149, 154, 158, 163, 167, 171, 175, 179, 182, 184, 187, 188, 191, 191, 192, 193, 194, 193, 192, 191, 191, 188, 187, 184, 182, 179, 175, 171, 167, 163, 158, 154, 149, 144, 139, 133, 128, 122, 116, 110, 104, 98, 92, 86, 80, 74, 68, 63, 57, 52, 47, 42, 38, 33, 29, 25, 21, 17, 14, 12, 9, 8, 5, 5, 4, 3, 3, 3, 4, 5, 5, 8, 9, 12, 14, 17, 21, 25, 29, 33, 38, 42, 47, 52, 57, 63, 68, 74, 80, 86, 92, };
byte piano[]={ 127, 120, 112, 104, 96, 88, 79, 70, 61, 53, 46, 39, 35, 31, 30, 30, 31, 34, 38, 43, 48, 53, 59, 65, 71, 76, 81, 85, 89, 91, 93, 93, 93, 92, 92, 91, 90, 89, 88, 87, 86, 84, 82, 79, 76, 72, 68, 62, 57, 51, 46, 40, 35, 31, 28, 26, 26, 26, 28, 31, 34, 39, 44, 49, 55, 60, 65, 70, 74, 77, 80, 81, 83, 84, 84, 84, 84, 84, 84, 84, 85, 86, 87, 90, 94, 99, 105, 112, 119, 126, 133, 140, 146, 151, 156, 161, 165, 170, 174, 179, 182, 186, 188, 189, 190, 189, 188, 186, 184, 181, 180, 179, 178, 179, 180, 182, 184, 187, 189, 191, 192, 193, 193, 192, 191, 189, 186, 184, 181, 178, 175, 172, 171, 170, 170, 171, 173, 176, 180, 184, 188, 191, 193, 194, 195, 195, 194, 193, 191, 190, 190, 190, 190, 190, 191, 192, 192, 194, 195, 196, 197, 199, 200, 201, 201, 201, 200, 198, 195, 192, 187, 182, 177, 171, 165, 158, 152, 145, 137, 130, };
byte zero[]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

int t = 0;//time
char note = 'A'; // These will keep track of if two of the same notes are played in a row
char note_prv='B';
boolean play=1; // Used to cause a brief break in case of  ^^
boolean valid=1; // To make sure only the single letters we have defined as notes are interpreted as such

void setup(){
  Serial.begin(4800);
  establishContact();

  //set digital pins 0-7 as outputs
  for (int i=0;i<8;i++){
    pinMode(i,OUTPUT);
  }
  


  cli();//disable interrupts
  //set timer0 interrupt
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register to a default value
  OCR0A = 200;// = (16*10^6) / (40000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS10 bit for 64 prescaler
  TCCR0B |= (1 << CS00); 
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei();//enable interrupts
};


ISR(TIMER0_COMPA_vect){ 
  if (play){
    PORTD = piano[t];
    t++;
    if (t > 179){
      t = 0;
    }
  }
}


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

void set_freq(char note) { // Determine which frequency to play
  valid=0;
  switch (note){
  case ' ': play=0;break; // causes a glitch
  case 'a' :OCR0A=253;valid=1;break;
  case 'w' : OCR0A=234;valid=1;break;
  case 's': OCR0A=226;valid=1;break;
  case 'e': OCR0A=213;valid=1;break;
  case 'd': OCR0A=201;valid=1;break;
  case 'r': OCR0A=190;valid=1;break;
  case 'f': OCR0A=179;valid=1;break;
  case 'g': OCR0A=169;valid=1;break;
  case 'y': OCR0A=159;valid=1;break;
  case 'h': OCR0A=150;valid=1;break;
  case 'u': OCR0A=142;valid=1;break;
  case 'j': OCR0A=134;valid=1;break;
  case 'k': OCR0A=126;valid=1;break;
  case 'o': OCR0A=119;valid=1;break;
  case 'l': OCR0A=113;valid=1;break;
  case 'p': OCR0A=106;valid=1;break;
  case ';': OCR0A=100;valid=1;break;
//  case '['': OCR0A=96;valid=1;break;
//  case '\''': OCR0A=94;valid=1;break;
  }
}
void loop()
{

  if (Serial.available() > 0) { 
    play=1;
    if (valid){note_prv=note;} // 
    note = Serial.read();
    Serial.println(note);
    if (note == note_prv){
      set_freq(' '); 
    }
    else{
      set_freq(note);
    }
  }
}


