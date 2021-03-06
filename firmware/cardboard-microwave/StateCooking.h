#include "Arduino.h"

#ifndef STATE_COOKING_H
#define STATE_COOKING_H

#include "ClockDisplay.h"

const int TICK_LENGTH_MS = 200; // each tick is 200ms, instead of a full second
const int NUMBER_OF_COMPLETE_BEEPS = 3;
const long TIME_BETWEEN_COMPLETE_BEEPS_MS = 800; // when playing complete sound
                                                 // how long to wait in between

/**
 * This class countdown "ticks". where each tick has a duration in ms. In it's naive form,
 * each tick is 1sec long, and this is simply a seconds counter
 */
class Countdown
{
  private:
    int _tickLengthMs; // the length of each tick  
    int _ticksRemaining; // number of ticks
    unsigned long _previousMillis;   // will store last time this was updated
 
  public:
    Countdown();

    /**
     * This method updates the countdown (if needed). It should be called
     * from the main loop
     */
    void Update(unsigned long currentMillis);
    
    /**
     * This method updates the remaining ticks
     */
    void setTicksRemaining(int ticksRemaining);

    /**
     * Returns the number of ticks remaining
     */
    int getTicksRemaining();
};

/**
 * This method will repeat the cooking sound until we call stopMusic
 */
class CookingMusicRepeat
{
  private:
    int soundLengthMs; // the length of music track  
    boolean playOn = false;
    unsigned long previousMillis;   // will store last time this was updated
 
  public:
    CookingMusicRepeat(); 

    /**
     * This method restarts the sound if it ended. It should be called
     * from the main loop
     */
    void Update(unsigned long currentMillis);

    /**
     * This method stops the sound
     */
    void stopMusic();

    /**
     * This method starts the music
     */
    void startMusic();
};

/**
 * This class handles the Cooking state. It should play the microwave cooking sound, and update
 * the LCD to show the remianing time. When finished, it will beep several times.
 */
class StateCooking {
  private:
    Countdown cdown;
    CookingMusicRepeat cookingMusicRepeat;
    boolean _done = false; // is the state done?
    
    ClockDisplay* pClockDisplay;
    byte _stopButtonPin;

  public:
    StateCooking(ClockDisplay* c, byte stopButtonPin);
    void Update(unsigned long currentMillis);

    /**
     * This method resets the reminaing time and starts the state
     */
    void start();

    /**
     * This method ends the state
     */
    void done();

    /**
     * Is the state finished executing?
     */
    boolean isDone();
};

#endif 
