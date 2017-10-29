#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include "AssetManager.h"

class AudioManager
{
private:
    static AudioManager* sInstance;

    AssetManager* assetManager;

public:
    static AudioManager* instance();
    static void release();

    void play_music(std::string filename, int loops = -1);
    void pause_music();
    void resume_music();

    void play_sfx(std::string filename, int loops = 0, int channel = 0);

private:
    AudioManager();
    ~AudioManager();
};


#endif //_AUDIOMANAGER_H