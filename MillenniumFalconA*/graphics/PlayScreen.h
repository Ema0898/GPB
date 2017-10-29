#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "../game/Level.h"

class PlayScreen : public GameEntity
{
private:
    Timer* mTimer;
    InputManager* inputManager;
    AudioManager* audioManager;

    BackgroundStars* mStars;

    Texture* mStartLabel;

    Level* mLevel;

    Player* mPlayer;

    float mLevelStartTimer;
    float mLevelStartDelay;

    bool mGameStarted;
    bool mLevelStarted;
    int mCurrentStage;

private:
    void start_next_level();

public:
    PlayScreen();
    ~PlayScreen();

    void start_new_game();
    bool game_over();
    void update();
    void render();

};


#endif //_PLAYSCREEN_H