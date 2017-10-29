#include "AnimatedTexture.h"

// Frame Count is how many images does the animation have
AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
        : Texture(filename, x, y, w, h)
{
    mTimer = Timer::instance();
    mStartX = x;
    mStartY = y;
    mFrameCount = frameCount;
    mAnimationSpeed = animationSpeed;
    mTimePerFrame = animationSpeed / mFrameCount;
    mAnimationTimer = 0.0f;
    mAnimationDirection = animationDir;
    animation_done = false;
    mWrapMode = loop;
}

AnimatedTexture::~AnimatedTexture()
{

}

void AnimatedTexture::set_wrap_mode(WRAP_MODE mode)
{
    mWrapMode = mode;
}

void AnimatedTexture::reset_animation()
{
    mAnimationTimer = 0.0f;
    animation_done = false;
}

bool AnimatedTexture::is_animating()
{
    return !animation_done;
}

void AnimatedTexture::update()
{
    if (!animation_done)
    {
        mAnimationTimer += mTimer->delta_time();

        if (mAnimationTimer >= mAnimationSpeed)
        {
            if (mWrapMode == loop)
            {
                mAnimationTimer -= mAnimationSpeed;
            }
            else
            {
                animation_done = true;
                mAnimationTimer = mAnimationSpeed - mTimePerFrame;
            }
        }

        if (mAnimationDirection == horizontal)
        {
            mClipRect.x = mStartX + (int) (mAnimationTimer / mTimePerFrame) * mWidth;
        }
        else
        {
            mClipRect.y = mStartY + (int) (mAnimationTimer / mTimePerFrame) * mHeight;
        }
    }
}
