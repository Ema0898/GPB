#include "BackgroundStars.h"

BackgroundStars* BackgroundStars::sInstance = nullptr;

BackgroundStars* BackgroundStars::instance()
{
    if (sInstance == nullptr)
        sInstance = new BackgroundStars();

    return sInstance;
}

void BackgroundStars::release()
{
    delete sInstance;
    sInstance = nullptr;
}

BackgroundStars::BackgroundStars()
{
    for (int i = 0; i < LAYER_COUNT; ++i)
        mLayers[i] = new StarLayer(i);
}

BackgroundStars::~BackgroundStars()
{
    for (int i = 0; i < LAYER_COUNT; ++i)
    {
        delete mLayers[i];
        mLayers[i] = nullptr;
    }
}

void BackgroundStars::scroll(bool scroll)
{
    Star::set_scroll(scroll);
}

void BackgroundStars::update()
{
    for (int i = 0; i < LAYER_COUNT; ++i)
        mLayers[i]->update();
}

void BackgroundStars::render()
{
    for (int i = 0; i < LAYER_COUNT; ++i)
        mLayers[i]->render();
}



