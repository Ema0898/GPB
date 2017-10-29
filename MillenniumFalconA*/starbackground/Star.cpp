#include "Star.h"

bool Star::sScroll = false;

void Star::set_scroll(bool scroll)
{
    sScroll = scroll;
}

Star::Star(int layer)
        : Texture("star2.png", 0, 0, 4, 4)
{
    mTimer = Timer::instance();

    int star_color = rand() % 4;
    mClipRect.x = star_color * 4;

    set_pos(Vector2(rand() % Graphics::instance()->SCREEN_WIDTH, rand() % Graphics::instance()->SCREEN_HEIGHT));

    mFlickerTimer = 0.0f;
    mFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f ;

    float invLayer = 1.0f / layer;
    set_scale(VEC2_ONE * invLayer);

    mScrollSpeed = 4.0f / layer;
}

Star::~Star()
{
    mTimer = nullptr;
}

void Star::scroll_star()
{
    translate(VEC2_UP * mScrollSpeed, world);

    Vector2 pos = get_pos(local);

    if (pos.y > Graphics::instance()->SCREEN_HEIGHT)
    {
        pos.y = 0.0f;
        pos.x = rand() % Graphics::instance()->SCREEN_WIDTH;
        set_pos(pos);
    }
}

void Star::update()
{
    mFlickerTimer += mTimer->delta_time();
    if (mFlickerTimer >= mFlickerSpeed)
    {
        mVisible = !mVisible;
        mFlickerTimer = 0.0f;
    }

    if (sScroll)
        scroll_star();
}

void Star::render()
{
    if (mVisible)
        Texture::render();
}

