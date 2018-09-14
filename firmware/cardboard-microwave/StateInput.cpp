#include "StateInput.h"
#include "Arduino.h"
#include "sounds.h"

#include <PCM.h>
// Timers based on - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 

StateInput::StateInput(Keypad k, byte startButtonPin, byte stopButtonPin) :
    _keypad(k), _startButtonPin(startButtonPin), _stopButtonPin(stopButtonPin) {};

void StateInput::Update(unsigned long currentMillis)
{
      // read keypad
    /*
    char key = _keypad.getKey();
    Serial.println(key);
    if (key != NO_KEY){
        Serial.println(key);
        //clockDisplay.print(key, DEC);
        //clockDisplay.writeDisplay();    
        startPlayback(sound_key, sizeof(sound_key));
    }  
    */
  
    // read buttons
    int startButtonState = digitalRead(_startButtonPin);
    int stopButtonState = digitalRead(_stopButtonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (startButtonState == LOW || stopButtonState == LOW) {
        Serial.println("Hi!");  
        startPlayback(sound_key, sizeof(sound_key));
        delay(500); // a simple "debouncing". Replace with proper one
    } else {
    }
};

void StateInput::start() {
    _done = false;
}

void StateInput::stop() {
    _done = true;    
}

boolean StateInput::isDone() {
    return _done;
}
