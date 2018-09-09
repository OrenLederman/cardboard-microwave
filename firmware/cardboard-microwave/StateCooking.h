#include "Arduino.h"

const int TICK_LENGTH_MS = 200; // each tick is 200ms, instead of a full second

#ifndef STATE_COOKING_H
#define STATE_COOKING_H


class Countdown
{
  private:
    int tickLengthMs; // the length of each tick  
    int ticksRemaining; // number of ticks
    unsigned long previousMillis;   // will store last time this was updated
 
  public:
    Countdown(int tickLengthMsInit, int ticksRemainingInit);
    void Update(unsigned long currentMillis);
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
    StateCooking(int ticks);
    void Update(unsigned long currentMillis);
};

#endif 
