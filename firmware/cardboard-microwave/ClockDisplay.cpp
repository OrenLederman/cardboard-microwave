#include "ClockDisplay.h"



ClockDisplay::ClockDisplay()
{
  // Init 7-segment
  clockDisplay.begin(0x70);  // pass in the address
  clockDisplay.print(10000, DEC);
  clockDisplay.writeDisplay();
};

