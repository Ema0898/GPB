#include "Texture.h"


Texture::Texture()
{

}

Texture::Texture(std::string filename)
{
    mGraphics = Graphics::instance();

    mTexture = AssetManager::instance()->get_texture(filename);

    SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

    mClipped = false;

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
    mGraphics = Graphics::instance();
    mTexture = AssetManager::instance()->get_texture(filename);

    mClipped = true;
    mWidth = w;
    mHeight = h;

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;

    mClipRect.x = x;
    mClipRect.y = y;
    mClipRect.w = mWidth;
    mClipRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontpath, int size, SDL_Color color)
{
    mGraphics = Graphics::instance();
    mTexture = AssetManager::instance()->get_text(text, fontpath, size, color);

    mClipped = false;

    SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);

    mRenderRect.w = mWidth;
    mRenderRect.h = mHeight;
}

Texture::~Texture()
{
    mTexture = nullptr;
    mGraphics = nullptr;
}

void Texture::render()
{
    Vector2 pos = get_pos(world);
    Vector2 scale = get_scale(world);

    mRenderRect.x = (int) (pos.x - mWidth * scale.x * 0.5f);
    mRenderRect.y = (int) (pos.y - mHeight * scale.y * 0.5f);
    mRenderRect.w = (int) (mWidth * scale.x);
    mRenderRect.h = (int) (mHeight * scale.y);

    mGraphics->draw_texture(mTexture, (mClipped) ? &mClipRect : nullptr, &mRenderRect, rotation(world));
}

