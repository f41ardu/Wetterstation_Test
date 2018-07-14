/*





ATMEL ATTINY45 or 85/ ARDUINO 
Simple setup, connect an IR LED to Pin 0 or Pin 13 if you are using an ARDUINO

                         +-\/-+
Reset / Ain0 (D 5) PB5  1|    |8  Vcc (+)
        Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1, SKC
        Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1, MISO            IR    220 Ohm
              (-)  GND  4|    |5  PB0 (D 0) pwm0, AREF, MOSI -----LED----|||||------< GND
                         +----+
*/
 
// Pin where we connect the IR LED 
// For Attiny 45/85
int pinIRLED = PB0;                                      // assign the Infrared emitter diode to pin 0 (PB0) as show above 

// For Arduino use Pin 13 
// int pinIRLED = 13;                                   // assign the Infrared emitter diode to pin 0 (PB0) if you use an Arduino Board


int  modulate = 13;                                    // 13 us = 38.4 Khz
// 
//                         ON    OFf  ON  OFF  ON  OFF  ON  OFF  
unsigned int Nikon[10] = {2000,27850,390,1580,410,3580,400,63200,0,0};
/* 
Init PIN MODE
*/
void setup() {
     
  pinMode(pinIRLED, OUTPUT);                            // set the pin as an output
}

/* 
The main loop. We send the IR code twise and forever
You may add a switch to trigger the Picture manually 
*/ 

void loop() {

  takePicture();
  delay(1000); 

}
