#ifndef _STARLAYER_H
#define _STARLAYER_H

#include "Star.h"

class StarLayer
{
private:
    static const int STAR_COUNT = 30;
    Star* mStarArray[STAR_COUNT];

public:

    StarLayer(int layer);
    ~StarLayer();

    void update();
    void render();

};


#endif //_STARLAYER_H