#include "Arduino.h"
#include <Wire.h>   //adafruit 7-segment
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

// Note - using I2C, pins A4 and A5
// Required for the 7 segment display. Taken form Adafruit's example
#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif


#ifndef CLOCK_DISPLAY_H
#define CLOCK_DISPLAY_H

/**
 * This class the clock display
 */
class ClockDisplay {
  private:
    Adafruit_7segment clockDisplay = Adafruit_7segment();
    int mmss; // time is MM:SS format

  public:
    ClockDisplay();

    /**
     * Initializes the display. Call at setup().
     */
    void Init(); 

    /**
    * Resets the display to --:--
    */
    void Reset();

    /**
    * returns the current time as secons
    */
    int getTimeInSeconds();

    /**
    * Sets MM:SS time based on provided seconds
    */
    void setTimeSeconds(int seconds);

    /**
    * Adds a digit to the time from the right. If the display is full (4 digits),
    * no change will occure
    */
    void AddDigit(int digit);
};

#endif 
