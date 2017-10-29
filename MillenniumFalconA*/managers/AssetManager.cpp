#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::instance()
{
    if (sInstance == nullptr)
        sInstance = new AssetManager();

    return sInstance;
}

void AssetManager::release()
{
    delete sInstance;
    sInstance = nullptr;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
    for (auto tex : mTextures)
    {
        if (tex.second != nullptr)
            SDL_DestroyTexture(tex.second);

    }

    mTextures.clear();

    for (auto text : mText)
    {
        if (text.second != nullptr)
            SDL_DestroyTexture(text.second);
    }

    mText.clear();

    for (auto font : mFonts)
    {
        if (font.second != nullptr)
            TTF_CloseFont(font.second);
    }

    mFonts.clear();

    for (auto music : mMusic)
    {
        if (music.second != nullptr)
            Mix_FreeMusic(music.second);
    }

    mMusic.clear();

    for (auto sfx : mSFX)
    {
        if (sfx.second != nullptr)
            Mix_FreeChunk(sfx.second);
    }

    mSFX.clear();
}

SDL_Texture* AssetManager::get_texture(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mTextures[fullPath] == nullptr)
        mTextures[fullPath] = Graphics::instance()->load_texture(fullPath);

    return mTextures[fullPath];
}

TTF_Font* AssetManager::get_font(std::string filename, int size)
{
    std::string fullpath = SDL_GetBasePath();
    fullpath.append("assets/" + filename);
    std::string key = fullpath + (char) size;

    if (mFonts[key] == nullptr)
    {
        mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);

        if (mFonts[key] == nullptr)
            std::cout << "Font Loading: mPath: " << fullpath << ", Error: " << TTF_GetError() << std::endl;
    }

    return mFonts[key];
}

SDL_Texture* AssetManager::get_text(std::string text, std::string filename, int size, SDL_Color color)
{
    TTF_Font* font = get_font(filename, size);
    std::string key = text + filename + (char) size + (char) color.r + (char) color.b + (char) color.g;

    if (mText[key] == nullptr)
    {
        mText[key] = Graphics::instance()->create_text_texture(font, text, color);
    }

    return mText[key];
}

Mix_Music* AssetManager::get_music(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mMusic[fullPath] == nullptr)
    {
        mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
        if (mMusic[fullPath] == nullptr)
        {
            std::cout << "Music Loading Error: mPath: " << fullPath << ", Error: " << Mix_GetError() << std::endl;
        }
    }

    return mMusic[fullPath];
}

Mix_Chunk* AssetManager::get_sfx(std::string filename)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("assets/" + filename);

    if (mSFX[fullPath] == nullptr)
    {
        mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
        if (mSFX[fullPath] == nullptr)
        {
            std::cout << "SFX Loading Error: mPath: " << fullPath << ", Error: " << Mix_GetError() << std::endl;
        }
    }

    return mSFX[fullPath];
}
