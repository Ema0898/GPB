#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::instance()
{
    if (sInstance == nullptr)
        sInstance = new AudioManager();

    return sInstance;
}

void AudioManager::release()
{
    delete sInstance;
    sInstance = nullptr;
}

AudioManager::AudioManager()
{
    assetManager = AssetManager::instance();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        std::cout << "Mixer Initialization Error: " << Mix_GetError() << std::endl;
    }
}

AudioManager::~AudioManager()
{
    assetManager = nullptr;

    Mix_Quit();
}

void AudioManager::play_music(std::string filename, int loops)
{
    Mix_PlayMusic(assetManager->get_music(filename), loops);
}

void AudioManager::pause_music()
{
    if (Mix_PlayingMusic() != 0)
        Mix_PauseMusic();
}

void AudioManager::resume_music()
{
    if (Mix_PausedMusic() != 0)
        Mix_ResumeMusic();
}

void AudioManager::play_sfx(std::string filename, int loops, int channel)
{
    Mix_PlayChannel(channel, assetManager->get_sfx(filename), loops);
}


