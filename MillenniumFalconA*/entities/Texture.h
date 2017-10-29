#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <iostream>
#include "GameEntity.h"
#include "../graphics/Graphics.h"
#include "../managers/AssetManager.h"

class Texture : public GameEntity
{
protected:

    SDL_Texture* mTexture;
    Graphics* mGraphics;

    int mWidth;
    int mHeight;

    bool mClipped;
    SDL_Rect mRenderRect;
    SDL_Rect mClipRect;

public:

    Texture();
    Texture(std::string filename);
    Texture(std::string filename, int x, int y, int w, int h);
    Texture(std::string text, std::string fontpath, int size, SDL_Color color);
    ~Texture();

    virtual void render();
};


#endif //_TEXTURE_H