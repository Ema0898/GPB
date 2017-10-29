#ifndef _BACKGROUNDSTARS_H
#define _BACKGROUNDSTARS_H

#include "StarLayer.h"

class BackgroundStars
{
private:
    static BackgroundStars* sInstance;

    static const int LAYER_COUNT = 3;
    StarLayer* mLayers[LAYER_COUNT];

public:
    static BackgroundStars* instance();
    static void release();

    void scroll(bool scroll);
    void update();
    void render();

private:
    BackgroundStars();
    ~BackgroundStars();

};


#endif //_BACKGROUNDSTARS_H