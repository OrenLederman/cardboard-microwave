#include "ClockDisplay.h"



ClockDisplay::ClockDisplay()
{
};

void ClockDisplay::Init()
{
  // Init 7-segment
  clockDisplay.begin(0x70);  // pass in the address
  this->Reset();
};

void ClockDisplay::Reset()
{
  clockDisplay.print(10000, DEC);
  clockDisplay.drawColon(true);
  clockDisplay.writeDisplay();
  mmss = 0;
};

int ClockDisplay::getTimeInSeconds()
{
  int mm = mmss / 100;
  int ss = mmss % 100;
  return mm * 60 + ss;
}

void ClockDisplay::setTimeSeconds(int seconds)
{
  int mm = seconds / 60;
  int ss = seconds % 60;
  mmss = mm*100 + ss;
  clockDisplay.print(mmss, DEC);
  clockDisplay.drawColon(true);  
  clockDisplay.writeDisplay();  
}

void ClockDisplay::AddDigit(int digit)
{
  if (mmss < 1000) {
    mmss = (mmss * 10) + digit;
     Serial.println(mmss);
    clockDisplay.print(mmss, DEC);
    clockDisplay.drawColon(true);    
    clockDisplay.writeDisplay();  
  }
}

