#include "Arduino.h"

const int TICK_LENGTH_MS = 200; // each tick is 200ms, instead of a full second

#ifndef STATE_COOKING_H
#define STATE_COOKING_H


class Countdown
{
  private:
    int _tickLengthMs; // the length of each tick  
    int _ticksRemaining; // number of ticks
    unsigned long _previousMillis;   // will store last time this was updated
 
  public:
    Countdown();
    void Update(unsigned long currentMillis);
    void setTicksRemaining(int ticksRemaining);
};

class CookingMusicRepeat
{
  private:
    int soundLengthMs; // the length of music track  
    boolean playOn = true;
    unsigned long previousMillis;   // will store last time this was updated
 
  public:
    CookingMusicRepeat(); 
    void Update(unsigned long currentMillis);
    void stopMusic();
};


class StateCooking {
  private:
    Countdown cdown;
    CookingMusicRepeat cookingMusicRepeat;

  public:
    StateCooking();
    void Update(unsigned long currentMillis);
    void reset(int ticksRemaining);
};

#endif 
