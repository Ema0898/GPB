#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

Graphics* Graphics::instance()
{
    if (sInstance == nullptr)
        sInstance = new Graphics();

    return sInstance;
}

void Graphics::release()
{
    delete sInstance;
    sInstance = nullptr;

    sInitialized = false;
}

bool Graphics::initialized()
{
    return sInitialized;
}

Graphics::Graphics()
{
    mBackBuffer = nullptr;
    sInitialized = init();
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;

    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Graphics::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("MillenniumFalcon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr)
    {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr)
    {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

    int flags = IMG_INIT_PNG;
    if (!IMG_Init(flags) & flags)
    {
        std::cout << "Image Initialization Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "TTF Initialization Error: " << TTF_GetError() << std::endl;
        return false;
    }

    mBackBuffer = SDL_GetWindowSurface(mWindow);

    return true;
}

SDL_Texture* Graphics::load_texture(std::string path)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cout << "Image Load Error: " << IMG_GetError() << " , mPath: " << path <<  std::endl;
        return texture;
    }

    texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (texture == nullptr)
    {
        std::cout << "Create Texture Error: " << IMG_GetError() << std::endl;
        return texture;
    }

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* Graphics::create_text_texture(TTF_Font *font, std::string text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cout << "Text Render Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer,  surface);
    if (texture == nullptr)
    {
        std::cout << "Text Texture Creation Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void Graphics::clear_back_buffer()
{
    SDL_RenderClear(mRenderer);
}

void Graphics::draw_texture(SDL_Texture *texture, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(mRenderer, texture, clip, rend, angle, nullptr, flip);
}

void Graphics::draw_line(float startX, float startY, float endX, float endY)
{
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mRenderer, startX, startY, endX, endY);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Graphics::render()
{
    SDL_RenderPresent(mRenderer);
}
