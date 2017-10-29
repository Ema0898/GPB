#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::instance()
{
    if (sInstance == nullptr)
        sInstance = new Timer();

    return sInstance;
}

void Timer::release()
{
    delete sInstance;
    sInstance = nullptr;
}

Timer::Timer()
{
    reset();
    mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::reset()
{
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}

float Timer::delta_time()
{
    return mDeltaTime;
}

void Timer::time_scale(float time)
{
    mTimeScale = time;
}

float Timer::time_scale()
{
    return mTimeScale;
}

void Timer::update()
{
    mElapsedTicks = SDL_GetTicks() - mStartTicks;
    mDeltaTime = mElapsedTicks * 0.001f; // Convert to seconds
}

