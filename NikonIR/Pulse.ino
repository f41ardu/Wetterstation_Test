/* 
We simulate the IR Pulse by fast modulated switching the IR LED 
using a duyty cycle of 34.8 Khz (modulate =13 us).  
The function delayMicroseconfs is precise enough for my Nikon D-40 

Modulate (Pulse) the the IR LED   
*/ 
void pulseON(int pulseTime, int pulseLenght) {
  unsigned long endPulse = micros() + pulseTime;        // create the microseconds to pulse for
  while( micros() < endPulse) {
    digitalWrite(pinIRLED, HIGH);                       // turn IR on
    delayMicroseconds(pulseLenght);                     // half the clock cycle for 38Khz (26.32×10-6s) - e.g. the 'on' part of our wave
    digitalWrite(pinIRLED, LOW);                        // turn IR off
    delayMicroseconds(pulseLenght);                     //delay for the other half of the cycle to generate wave/ oscillation
  }
}

/* 
IR LED OFF
Modulate (Pulse) the the IR LED with 38.8 Khz, but LED is of, so we just wait ;-> 
*/ 
void pulseOFF(unsigned long startDelay) {
  digitalWrite(pinIRLED, LOW);  
  unsigned long endDelay = micros() + startDelay;       // create the microseconds to delay for
  while(micros() < endDelay);
}

/* 
activate IR LED 
*/ 
void takePicture() {
  int j = 0;
  int ontime = 0;
  int offtime= 0;
  for (int i=0; i < 2; i++) {
  do {
     ontime = Nikon[j];
     offtime = Nikon[j+1];
     pulseON(ontime,modulate);
     pulseOFF(offtime);
     j=j+2;
     } while ( offtime != 0); 
    j=0;      
    }                                                     // loop the signal twice.
}
