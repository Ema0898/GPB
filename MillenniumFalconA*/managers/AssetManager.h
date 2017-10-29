#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include <map>
#include <SDL2/SDL_mixer.h>
#include "../graphics/Graphics.h"

class AssetManager
{
private:

    static AssetManager* sInstance;

    std::map<std::string, SDL_Texture*> mTextures;
    std::map<std::string, SDL_Texture*> mText;
    std::map<std::string, TTF_Font*> mFonts;
    std::map<std::string, Mix_Music*> mMusic;
    std::map<std::string, Mix_Chunk*> mSFX;

public:

    static AssetManager* instance();
    static void release();

    SDL_Texture* get_texture(std::string filename);
    SDL_Texture* get_text(std::string text, std::string filename, int size, SDL_Color color);
    Mix_Music* get_music(std::string filename);
    Mix_Chunk* get_sfx(std::string filename);

private:

    AssetManager();
    ~AssetManager();

    TTF_Font* get_font(std::string filename, int size);
};


#endif //GALAGA_ASSETMANAGER_H