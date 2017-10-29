#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Graphics
{
public:

    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

private:

    static Graphics* sInstance; // This class uses singleton
    static bool sInitialized;

    SDL_Window* mWindow;
    SDL_Surface*  mBackBuffer;
    SDL_Renderer* mRenderer;

public:
    static Graphics* instance();
    static void release();
    static bool initialized();

    SDL_Texture* load_texture(std::string path);
    SDL_Texture* create_text_texture(TTF_Font* font, std::string text, SDL_Color color);

    void clear_back_buffer();
    void draw_texture(SDL_Texture* texture, SDL_Rect* clip = nullptr, SDL_Rect* rend = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw_line(float startX, float startY, float endX, float endY);
    void render();

private:

    Graphics();
    ~Graphics();
    bool init();


};


#endif //_GRAPHICS_H