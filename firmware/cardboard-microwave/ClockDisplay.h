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

  public:
    ClockDisplay();
};

#endif 
