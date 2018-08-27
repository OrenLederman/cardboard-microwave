#include <Keypad.h> //keypad
#include <PCM.h>    //playing sounds

#include <Wire.h>   //adafruit 7-segment
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

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


Adafruit_7segment matrix = Adafruit_7segment();

// ---------------- Buttons & Interrupts -------------------------
const byte startButtonPin = 2;
const byte stopButtonPin = 3;
int startButtonState = 0;         // variable for reading the pushbutton status
int stopButtonState = 0;         // variable for reading the pushbutton status

// ---------------- Time keeping -------------------------

// ---------------- Init and main loop -------------------------
void setup(){
  Serial.begin(9600);

  // Init interrupts
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);

  //TODO-only enable interrupts when going to sleep
  //attachInterrupt(digitalPinToInterrupt(startButtonPin), wakeup, CHANGE);  
  //attachInterrupt(digitalPinToInterrupt(stopButtonPin), wakeup, CHANGE);  

  // Init 7-segment
  matrix.begin(0x70);  // pass in the address
  matrix.print(10000, DEC);
  matrix.writeDisplay();
  
  delay(500);
}
  
void loop(){
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

}

void wakeup() {
}

// ----------------- countdown -----------------
class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated
 
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }
 
  void Update(unsigned long currentMillis)
  {
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};

