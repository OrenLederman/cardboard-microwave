#include <Keypad.h> //keypad
#include <PCM.h>    //playing sounds

#include <Wire.h>   //adafruit 7-segment
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "StateCooking.h"

// --------------------- Sounds ------------------------------
// Note - using pin 11
#include"sounds.h"

// --------------------- Keypad ------------------------------
const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','H'}
};
byte rowPins[rows] = {9, 4, 5, 7}; //connect to the row pinouts of the keypad
byte colPins[cols] = {8, 10, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

// --------------------- 7-Segment LED ------------------------------
// Note - using I2C, pins A4 and A5
#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif


Adafruit_7segment clockDisplay = Adafruit_7segment();

// ---------------- Buttons & Interrupts -------------------------
const byte startButtonPin = 2;
const byte stopButtonPin = 3;
int startButtonState = 0;         // variable for reading the pushbutton status
int stopButtonState = 0;         // variable for reading the pushbutton status

// ---------------- Init and main loop -------------------------
StateCooking stateCooking;


void setup(){
  Serial.begin(9600);

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);

  // Init interrupts
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  // Init 7-segment
  matrix.begin(0x70);  // pass in the address
  matrix.print(10000, DEC);
  matrix.writeDisplay();

  //
  stateCooking.start(100);
  delay(500);
}
  
void loop(){
  // Loop is mostly empty. Using TIMER0 to schedule events (see function below)


  /*
  // read keypad
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    Serial.println(key);
    matrix.print(key, DEC);
    matrix.writeDisplay();    
    startPlayback(sound_key, sizeof(sound_key));
  }  

  
  // read buttons
  startButtonState = digitalRead(startButtonPin);
  stopButtonState = digitalRead(stopButtonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (startButtonState == LOW || stopButtonState == LOW) {
    Serial.println("Hi!");  
    startPlayback(sound_key, sizeof(sound_key));
    delay(500); // a simple "debouncing". Replace with proper one
  } else {
  }
  */
}

// ----------------- Sleep and wake up-----------------
void sleep() {
  //TODO-only enable interrupts when going to sleep
  //attachInterrupt(digitalPinToInterrupt(startButtonPin), wakeup, CHANGE);  
  //attachInterrupt(digitalPinToInterrupt(stopButtonPin), wakeup, CHANGE);  
}


void wakeup() {
  //TODO-disable button interrupts
}

// ----------------- Timer -----------------
// Interrupt is called once a millisecond. See - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 
SIGNAL(TIMER0_COMPA_vect) 
{
  unsigned long currentMillis = millis();

  //call states (based on which state is on now)
  stateCooking.Update(currentMillis);
}

