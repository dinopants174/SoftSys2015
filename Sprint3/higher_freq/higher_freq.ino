//original sine vector
//byte sine[] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119,};
//sine vector optimized to reach 5kHz
byte sine[] = {251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119, 127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251,};
int t = 0;//time

void setup(){
  //set pins as outputs
  for (int i=0;i<8;i++){
    pinMode(i,OUTPUT);
  }
  
  cli();//stop interrupts

  //set timer0 interrupt at 16MHz
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register to 0, corresponds to:
  OCR0A = 0;// = (16*10^6) / (16*10^6*1) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS00 bit for 1 prescaler, clock as fast as it can go
  TCCR0B |= (1 << CS00);//prescaler to 1 for timer 0   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();//allow interrupts

}//end setup

ISR(TIMER0_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//2.352 kHz code below
  PORTD = sine[t];
  t++;
  if (t > 99){
    t = 0;
  }
  //by changing t increment to 2, speeds up sine wave to 4.705 kHz, by changing t increment to 3,
  //speeds up sine wave to 6.904kHz
  
  //use while loop to speed up, produce sine wave at 16.75kHz frequency, weird behavior observed
  //FT has decaying exponential behavior in frequency domain
  while (t < 99){
    PORTD = sine[t];
    t++;
  }
  t = 0;

  //could be fixed so sine vector is symmetric and produces 5kHz wave
  if (t == 0) {
      while (t < 94){
        PORTD = sine[t];
        delayMicroseconds(1);
        t++;
      }
  } if(t == 94){
    while(t > 0) {
      t--;
      PORTD = sine[t];
      delayMicroseconds(1);
    }
  }
}

//produces 4.5kHz wave
  while (t < 94){
    PORTD = sine[t];
    delayMicroseconds(1);
    t++;
  }
  t=0;
}



void loop(){
  //do other things here
}
