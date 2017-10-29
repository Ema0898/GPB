#ifndef _STAR_H
#define _STAR_H

#include "../tools/Timer.h"
#include "../entities/Texture.h"

class Star : public Texture
{
private:
    static bool sScroll;

    Timer* mTimer;

    bool mVisible;
    float mFlickerTimer;
    float mFlickerSpeed;

    float mScrollSpeed;

public:

    static void set_scroll(bool scroll);

    Star(int layer);
    ~Star();

    void update();
    void render();

private:
    void scroll_star();
};


#endif //_STAR_H