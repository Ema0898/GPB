#ifndef _ANIMATEDTEXTURE_H
#define _ANIMATEDTEXTURE_H

#include "../tools/Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture
{
public:

    enum WRAP_MODE { once = 0, loop = 1 };

    enum ANIM_DIR { horizontal = 0, vertical = 1 };

private:
    Timer* mTimer;

    int mStartX;
    int mStartY;
    int mFrameCount;

    float mAnimationTimer;
    float mAnimationSpeed;
    float mTimePerFrame;

    WRAP_MODE mWrapMode;
    ANIM_DIR mAnimationDirection;

    bool animation_done;

public:
    AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
    ~AnimatedTexture();

    void set_wrap_mode(WRAP_MODE mode);

    void reset_animation();

    bool is_animating();

    void update();
};


#endif //_ANIMATEDTEXTURE_H