#include "Arduino.h"
#include <Keypad.h> //keypad

#ifndef STATE_INPUT_H
#define STATE_INPUT_H

/**
 * This class handles the Input state. Pressing a button will beep. Pressing
 * start button will finish this state
 */
class StateInput {
  private:
    boolean _done = false; // is the state done?
    Keypad* _keypad;
    byte _startButtonPin;
    byte _stopButtonPin;
    unsigned long previousMillis; // last time called. Needed for button debouncing

  public:
    StateInput(Keypad* k, byte startButtonPin, byte stopButtonPin);
    void Update(unsigned long currentMillis);

    /**
     * This method resets the reminaing time and starts the state
     */
    void start();

    /**
     * This method ends the state
     */
    void stop();

    /**
     * Is the state finished executing?
     */
    boolean isDone();
};

#endif 
