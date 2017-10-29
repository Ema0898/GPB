#ifndef _ENEMY_H
#define _ENEMY_H

#include "../entities/AnimatedTexture.h"

class Enemy : public GameEntity
{
public:
    enum STATES
    {
        flyIn, formation, dive, dead
    };


protected:

    Timer* mTimer;
    Texture* mTexture;

    STATES mCurrentState;

    int mCurrentPath;
    int mCurrentWayPoint;

    const float EPSILON = 5.0f;

    float mSpeed;
    int mIndex;
    Vector2 mTargetPostion;
    bool mChallengeStage;

protected:
    virtual void path_complete();

    virtual Vector2 formation_position() = 0;

    virtual void handle_formation_state();
    virtual void handle_dive_state() = 0;
    virtual void handle_dead_state() = 0;

    void handle_states();

public:
    static void create_paths();

    Enemy(int index,int path, bool challenge_state);
    Enemy();
    virtual ~Enemy();

    STATES get_current_state();
    void update();
    void render();
};


#endif //_ENEMY_H