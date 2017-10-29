#include "Enemy.h"
void Enemy::create_paths()
{
    int screen_mid_point = Graphics::instance()->SCREEN_WIDTH * 0.4f;

    int current_path = 0;

}

Enemy::Enemy(int path, int index, bool challenge_state)
{
    mTimer = Timer::instance();

    mCurrentPath = path;

    mCurrentState = flyIn;

    mCurrentWayPoint = 1;

    mTexture = nullptr;

    mSpeed = 275.0f;

    mIndex = index;
    mChallengeStage = challenge_state;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
    mTimer = nullptr;

    delete mTexture;
    mTexture = nullptr;
}

void Enemy::path_complete()
{
    if (mChallengeStage)
    {
        mCurrentState = dead;
    }
}

void Enemy::handle_formation_state()
{
    set_pos(formation_position());
}

void Enemy::handle_states()
{
    switch (mCurrentState)
    {
        case flyIn:
            break;
        case formation:
            handle_formation_state();
            break;
        case dive:
            handle_dive_state();
            break;
        case dead:
            handle_dead_state();
            break;
    }
}

Enemy::STATES Enemy::get_current_state()
{
    return mCurrentState;
}

void Enemy::update()
{
    if (is_active())
        handle_states();
}

void Enemy::render()
{
    if (is_active())
    {
        mTexture->render();
    }
}

