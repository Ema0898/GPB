#ifndef _TIMER_H
#define _TIMER_H

#include <SDL2/SDL.h>

class Timer
{
private:

    static Timer* sInstance;
    unsigned int mStartTicks;
    unsigned int mElapsedTicks;
    float mDeltaTime;
    float mTimeScale;

public:

    static Timer* instance();
    static void release();

    void reset();
    void update();

    float delta_time();
    void time_scale(float time);
    float time_scale();

private:
    Timer();
    ~Timer();

};


#endif //_TIMER_H