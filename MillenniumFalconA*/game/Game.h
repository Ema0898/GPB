#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <ctime>
#include "../managers/AudioManager.h"
#include "../managers/ScreenManager.h"
#include "../pathfinding/Grid.h"

class Game
{
private:
    const int FRAME_RATE = 60;

    static Game* sInstance;
    bool mQuit;

    Graphics* mGraphics;
    Timer* mTimer;
    AssetManager* assetManager;
    InputManager* inputManager;
    AudioManager* audioManager;
    Grid* grid;

    SDL_Event mEvents;

    ScreenManager* screenManager;

public:
    static Game* instance();
    static void release();
    void run();

private:
    Game();
    ~Game();

    void early_update();
    void update();
    void late_update();

    void render();
};


#endif //_GAMEMANAGER_H