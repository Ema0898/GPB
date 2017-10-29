#include "StarLayer.h"


StarLayer::StarLayer(int layer)
{
    for (int i = 0; i < STAR_COUNT; ++i)
        mStarArray[i] = new Star(layer);
}

StarLayer::~StarLayer()
{
    for (int i = 0; i < STAR_COUNT; ++i)
    {
        delete mStarArray[i];
        mStarArray[i] = nullptr;
    }
}

void StarLayer::update()
{
    for (int i = 0; i < STAR_COUNT; ++i)
        mStarArray[i]->update();
}

void StarLayer::render()
{
    for (int i = 0; i < STAR_COUNT; ++i)
        mStarArray[i]->render();
}

