#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H

#include "../graphics/StartScreen.h"
#include "../graphics/PlayScreen.h"

class ScreenManager
{
private:
    enum SCREENS
    {
        start, play
    };

    static ScreenManager* sInstance;
    InputManager* inputManager;

    BackgroundStars* mBackgroundStars;
    StartScreen* mStarScreen;
    PlayScreen* mPlayScreen;

    SCREENS current_screen;

public:
    static ScreenManager* instance();
    static void release();

    void update();
    void render();

private:
    ScreenManager();
    ~ScreenManager();
};


#endif //_SCREENMANAGER_H