#include "StateInput.h"
#include "Arduino.h"
#include "sounds.h"

#include <PCM.h>
// Timers based on - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 

StateInput::StateInput(Keypad* k, byte startButtonPin, byte stopButtonPin) :
    _startButtonPin(startButtonPin), _stopButtonPin(stopButtonPin) 
    {
      _keypad = k;
      previousMillis = 0;  
    };

void StateInput::Update(unsigned long currentMillis)
{
      // read keypad
    
    char key = _keypad->getKey();
    if ((key != NO_KEY)  && (currentMillis - previousMillis >= 200)){
        previousMillis = currentMillis;  // Remember the time
        Serial.println(key);
        //clockDisplay.print(key, DEC);
        //clockDisplay.writeDisplay();    
        startPlayback(sound_key, sizeof(sound_key));
    }  
    
    // read buttons
    int startButtonState = digitalRead(_startButtonPin);
    int stopButtonState = digitalRead(_stopButtonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if ((startButtonState == LOW || stopButtonState == LOW) && (currentMillis - previousMillis >= 200)) {
        previousMillis = currentMillis;  // Remember the time
        Serial.println("Hi!");  
        startPlayback(sound_key, sizeof(sound_key));
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
