#include "ClockDisplay.h"



ClockDisplay::ClockDisplay()
{
  previousMillis = 0;
};

void ClockDisplay::Init()
{
  // Init 7-segment
  clockDisplay.begin(0x70);  // pass in the address
  this->Reset();
};

void ClockDisplay::Reset()
{
  mmss = DISPLAY_EMPTY_VALUE;
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
}

void ClockDisplay::AddDigit(int digit)
{
  if (mmss == DISPLAY_EMPTY_VALUE)
  {
    mmss = 0;  
  }
  
  if (mmss < 1000) {
    mmss = (mmss * 10) + digit;
    Serial.println(mmss);
  }
}

void ClockDisplay::Update(unsigned long currentMillis)
{
  if((currentMillis - previousMillis) > updateInterval)  // time to update
  {
    previousMillis = millis();
    clockDisplay.print(mmss, DEC);
    clockDisplay.drawColon(true);    
    clockDisplay.writeDisplay();      
  }
}
