#include "StateInput.h"
#include "Arduino.h"
#include "sounds.h"
#include "ClockDisplay.h"

#include <PCM.h>
// Timers based on - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 

StateInput::StateInput(Keypad* k, ClockDisplay* c, byte startButtonPin, byte stopButtonPin)
    {
      pKeyboard = k;
      pClockDisplay = c;
      previousMillis = 0;  

      _startButtonPin = startButtonPin;
      _stopButtonPin = stopButtonPin;
    };

void StateInput::Update(unsigned long currentMillis)
{
      // read keypad
    
    char key = pKeyboard->getKey();
    if ((key != NO_KEY)  && (currentMillis - previousMillis >= 200)){
        previousMillis = currentMillis;  // Remember the time
        Serial.println(key);        
        startPlayback(sound_key, sizeof(sound_key));
        if (key != '*' && key != 'H') {
          int digit = key - '0'; // convert char to digit
          pClockDisplay->AddDigit(digit);
        }
    }  
    
    // read buttons
    int startButtonState = digitalRead(_startButtonPin);
    int stopButtonState = digitalRead(_stopButtonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is Low:
    if ((startButtonState == LOW || stopButtonState == LOW) && (currentMillis - previousMillis >= 200)) {
        previousMillis = currentMillis;  // Remember the time, basic debounce
        startPlayback(sound_key, sizeof(sound_key));
        
        if (startButtonState == LOW) {
          this->done();
        }

        if (stopButtonState == LOW) {
          this->start();
        }

    } else {
    }
};

void StateInput::start() {
    _done = false;
    pClockDisplay->Reset();
}

void StateInput::done() {
    _done = true;    
}

boolean StateInput::isDone() {
    return _done;
}
