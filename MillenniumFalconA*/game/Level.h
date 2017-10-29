#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include "../managers/InputManager.h"
#include "../entities/GameEntity.h"
#include "../starbackground/BackgroundStars.h"
#include "../player/Player.h"
#include "../enemies/TIEFighter.h"

class Level : public GameEntity
{
public:
    enum LEVEL_STATES
    {
        running, finished, gameover
    };

private:
    Timer* mTimer;

    BackgroundStars* mStars;

    int mStage;
    bool mStageStarted;
    float mLabelTimer;

    Texture* mStageLabel;
    float mStageLabelOnScreen;
    float mStageLabelOffScreen;

    Texture* mReadyLabel;
    float mReadyLabelOnScreen;
    float mReadyLaeblOffScreen;

    Texture* mGameOverLabel;
    bool mGameOver;
    float mGameOverDelay;
    float mGameOverTimer;
    float mGameOverLabelOnScreen;

    Player* mPlayer;
    bool mPlayerHit;
    float mPlayerRespawnDelay;
    float mPlayerRespawnTimer;
    float mPlayerRespawnLabelOnScreen;

    LEVEL_STATES mCurrentState;

    std::vector<TIEFighter*> mEnemies;

private:
    void start_stage();
    void handle_start_label();
    void handle_collisions();
    void handle_player_death();

    void handle_enemy_spawning();

public:
    Level(int stage, Player* player);
    ~Level();

    LEVEL_STATES get_state();
    void update();
    void render();
};


#endif //_LEVEL_H