#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::instance()
{
    if (sInstance == nullptr)
        sInstance = new ScreenManager();

    return sInstance;
}

void ScreenManager::release()
{
    delete sInstance;
    sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
    inputManager = InputManager::instance();
    mBackgroundStars = BackgroundStars::instance();

    mStarScreen = new StartScreen();
    mPlayScreen = new PlayScreen();

    current_screen = start;
}

ScreenManager::~ScreenManager()
{
    inputManager = nullptr;

    BackgroundStars::release();
    mBackgroundStars = nullptr;

    delete mStarScreen;
    mStarScreen = nullptr;

    delete mPlayScreen;
    mPlayScreen = nullptr;
}

void ScreenManager::update()
{
    mBackgroundStars->update();

    switch (current_screen)
    {
        case start:
            mStarScreen->update();

            if (inputManager->key_pressed(SDL_SCANCODE_RETURN))
            {
                current_screen = play;
                mStarScreen->reset_animation();
                mPlayScreen->start_new_game();
            }

            break;

        case play:
            mPlayScreen->update();

            if (mPlayScreen->game_over())
                current_screen = start;

            break;
    }

}

void ScreenManager::render()
{
    mBackgroundStars->render();

    switch (current_screen)
    {
        case start:
            mStarScreen->render();
            break;

        case play:
            mPlayScreen->render();
            break;
    }
}

