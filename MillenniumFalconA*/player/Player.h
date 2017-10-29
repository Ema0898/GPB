#ifndef _PLAYER_H
#define _PLAYER_H

#include "../entities/AnimatedTexture.h"
#include "../managers/InputManager.h"
#include "../managers/AudioManager.h"
#include "../pathfinding/Grid.h"
#include "../pathfinding/AStar.h"

class Player : public GameEntity
{
private:
    Timer* mTimer;
    InputManager* inputManager;
    AudioManager* audioManager;
    Grid* grid;
    AStar* aStar;

    bool mVisible;
    bool mAnimating;

    int mScore;
    int mLives;

    Texture* mShip;
    AnimatedTexture* mDeathAnimation;

    float mMoveSpeed;
    Vector2 mMoveBounds;
    Vector2 mDestiny;

private:
    void handle_movement();

public:
    Player();
    ~Player();

    void set_visible(bool visible);
    bool is_animating();
    int get_score();
    int get_lives();
    void add_score(int change);
    void was_hit();

    void update();
    void render();
};


#endif //_PLAYER_H