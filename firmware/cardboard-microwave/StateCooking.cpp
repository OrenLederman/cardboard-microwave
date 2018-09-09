#include "StateCooking.h"
#include "Arduino.h"
#include "sounds.h"

#include <PCM.h>
// Timers based on - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 


Countdown::Countdown() 
{
    _previousMillis = 0;
    _tickLengthMs = TICK_LENGTH_MS;
};
 
void Countdown::Update(unsigned long currentMillis)
{
    if((_ticksRemaining  > 0) && (currentMillis - _previousMillis >= _tickLengthMs))
    {
      _previousMillis = currentMillis;  // Remember the time
      _ticksRemaining  = _ticksRemaining  - 1;
      Serial.println(_ticksRemaining );
    }
};

void Countdown::setTicksRemaining(int ticksRemaining)
{
  _ticksRemaining = ticksRemaining;
}

CookingMusicRepeat::CookingMusicRepeat() 
{
    soundLengthMs = sizeof(sound_cooking)/8000;
    previousMillis = 0;
};
 
void CookingMusicRepeat::Update(unsigned long currentMillis)
{
    if((playOn) && (currentMillis - previousMillis >= soundLengthMs))
    {
      previousMillis = currentMillis;  // Remember the time
      startPlayback(sound_cooking, sizeof(sound_cooking));
      Serial.println("Starting music");
    }
};

void CookingMusicRepeat::stopMusic()
{
    Serial.println("Stopped music");
    playOn = false;
    stopPlayback();
};

StateCooking::StateCooking() {};

void StateCooking::Update(unsigned long currentMillis)
{
      cdown.Update(currentMillis);
      cookingMusicRepeat.Update(currentMillis);    
  
      // when countdown is over, stop music, beep X times, and end state
      //cookingMusicRepeat.stopMusic();
      // beep X times
      // switch to other state
};

void StateCooking::reset(int ticksRemaining) {
  cdown.setTicksRemaining(ticksRemaining);
}

