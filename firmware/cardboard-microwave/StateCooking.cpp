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

int Countdown::getTicksRemaining()
{
    return _ticksRemaining;
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

void CookingMusicRepeat::startMusic()
{
    Serial.println("Starting music");
    playOn = true;
};

void CookingMusicRepeat::stopMusic()
{
    Serial.println("Stopped music");
    playOn = false;
    stopPlayback();
};

StateCooking::StateCooking(ClockDisplay* c, byte stopButtonPin)
{
   pClockDisplay = c;
   _stopButtonPin = stopButtonPin;
}

void StateCooking::Update(unsigned long currentMillis)
{
    cdown.Update(currentMillis);
    cookingMusicRepeat.Update(currentMillis);    
    pClockDisplay->setTimeSeconds(cdown.getTicksRemaining());

    // when countdown is over, stop music, beep X times, and end state
    if (cdown.getTicksRemaining() == 0) 
    {
        cookingMusicRepeat.stopMusic();
        // delay, let the display refresh
        delay(150);
        pClockDisplay->Update(currentMillis+150);
                
        // beep x times
        for (int i=0; i <  NUMBER_OF_COMPLETE_BEEPS; i++) {
            Serial.println("Beep..");
            startPlayback(sound_complete, sizeof(sound_complete));
            delay(TIME_BETWEEN_COMPLETE_BEEPS_MS);
        }

        _done = true;
    }
};

void StateCooking::start() {
    int ticksRemaining = pClockDisplay->getTimeInSeconds();
    cdown.setTicksRemaining(ticksRemaining);
    cookingMusicRepeat.startMusic();
    _done = false;
}

void StateCooking::done() {
    cdown.setTicksRemaining(0);
    cookingMusicRepeat.stopMusic();
    _done = true;    
}

boolean StateCooking::isDone() {
    return _done;
}
