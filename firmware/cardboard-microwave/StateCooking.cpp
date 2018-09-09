#include "StateCooking.h"
#include "Arduino.h"
#include "sounds.h"

#include <PCM.h>
// Timers based on - https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers 


Countdown::Countdown(int tickLengthMsInit, int ticksRemainingInit) 
{
    ticksRemaining = ticksRemainingInit;
    tickLengthMs = tickLengthMsInit;
    previousMillis = 0;
};
 
void Countdown::Update(unsigned long currentMillis)
{
    if((ticksRemaining > 0) && (currentMillis - previousMillis >= tickLengthMs))
    {
      previousMillis = currentMillis;  // Remember the time
      ticksRemaining = ticksRemaining - 1;
      Serial.println(ticksRemaining);
    }
};

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

StateCooking::StateCooking(int ticks) : cdown(TICK_LENGTH_MS,ticks) {};

void StateCooking::Update(unsigned long currentMillis)
{
      cdown.Update(currentMillis);
      cookingMusicRepeat.Update(currentMillis);    
  
      // when countdown is over, stop music, beep X times, and end state
      //cookingMusicRepeat.stopMusic();
      // beep X times
      // switch to other state
};

