#include <PCM.h>
#include "sounds.h"

#include <Keypad.h> //keypad
#include <Wire.h>   //adafruit 7-segment
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//#include "StateCooking.h"
#include "StateInput.h"

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


// ---------------- Buttons & Interrupts -------------------------
const byte startButtonPin = 2;
const byte stopButtonPin = 3;

// --------------------- 7-Segment LED ------------------------------
// Note - using I2C, pins A4 and A5
#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_7segment clockDisplay = Adafruit_7segment();

// ---------------- States -------------------------
//StateCooking stateCooking;
StateInput stateInput(keypad, startButtonPin, stopButtonPin);

const byte STATE_NONE = 0;
const byte STATE_INPUT = 1;
const byte STATE_COOKING = 2;
const byte STATE_SLEEP = 3;

byte state = STATE_NONE; // init starting state


// ---------------- Init and main loop -------------------------

void setup(){
  Serial.begin(9600);

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  //OCR0A = 0xAF;
  //TIMSK0 |= _BV(OCIE0A);

  // Init interrupts
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  // Init 7-segment
  clockDisplay.begin(0x70);  // pass in the address
  clockDisplay.print(10000, DEC);
  clockDisplay.writeDisplay();

  //
  state = STATE_INPUT;
  stateInput.start();
  delay(500);
}
  
void loop(){
  
  
  // Loop is mostly empty. Using TIMER0 to schedule events (see function below)
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
  switch(state) {
    case STATE_INPUT:
      stateInput.Update(currentMillis);
      break;
    case STATE_COOKING:
      //stateCooking.Update(currentMillis);
      break;
    default:
      Serial.println("No state?");
  }  
}

