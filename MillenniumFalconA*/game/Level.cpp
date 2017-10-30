#include "Level.h"

Level::Level(int stage, Player* player)
{
    mTimer = Timer::instance();
    mStars = BackgroundStars::instance();

    mStage = stage;
    mStageStarted = false;
    mLabelTimer = 0.0f;

    mStageLabel = new Texture("Stage", "Starjedi.ttf", 32, { 75, 75, 200 });
    mStageLabel->set_parent(this);
    mStageLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.5f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mReadyLabel = new Texture("Ready", "Starjedi.ttf", 32, { 150, 0, 0 });
    mReadyLabel->set_parent(this);
    mReadyLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.5f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mGameOverLabel = new Texture("GameOver", "emulogic.ttf", 32, { 150, 0, 0 });
    mGameOverLabel->set_parent(this);
    mGameOverLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.4f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mPlayer = player;
    mPlayerHit = false;
    mPlayerRespawnDelay = 3.0f;
    mPlayerRespawnTimer = 0.0f;
    mPlayerRespawnLabelOnScreen = 2.0f;

    mStageLabelOnScreen = 0.0f;
    mStageLabelOffScreen = 1.5f;

    mReadyLabelOnScreen = mStageLabelOnScreen;
    mReadyLaeblOffScreen = mReadyLabelOnScreen + 3.0f;

    mGameOver = false;
    mGameOverDelay = 6.0f;
    mGameOverTimer = 0.0f;
    mGameOverLabelOnScreen = 1.0f;

    mCurrentState = running;
}

Level::~Level()
{
    mTimer = nullptr;
    mStars = nullptr;

    delete mStageLabel;
    mStageLabel = nullptr;

    delete mReadyLabel;
    mReadyLabel = nullptr;

    mPlayer = nullptr;

    delete mGameOverLabel;
    mGameOverLabel = nullptr;

    for (int i = 0; i < mEnemies.size(); ++i)
    {
        delete mEnemies[i];
        mEnemies[i] = nullptr;
    }

}

void Level::start_stage()
{
    mStageStarted = true;
}

void Level::handle_start_label()
{
    mLabelTimer += mTimer->delta_time();
    if (mLabelTimer >= mStageLabelOffScreen)
    {
        mStars->scroll(true);
        if (mStage > 1)
        {
            start_stage();
        }
        else
        {
            if (mLabelTimer >= mReadyLaeblOffScreen)
            {
                start_stage();
                mPlayer->set_active(true);
                mPlayer->set_visible(true);
            }
        }
    }
}

void Level::handle_collisions()
{
    if (!mPlayerHit)
    {
        if (InputManager::instance()->instance()->key_pressed((SDL_SCANCODE_X)))
        {
            mPlayer->was_hit();

            mPlayerHit = true;
            mPlayerRespawnTimer = 0.0f;
            mPlayer->set_active(false);
            mStars->scroll(false);
        }
    }
}

void Level::handle_player_death()
{
    if (!mPlayer->is_animating())
    {
        if (mPlayer->get_lives() > 0)
        {
            if (mPlayerRespawnTimer == 0.0f)
                mPlayer->set_visible(false);

            mPlayerRespawnTimer += mTimer->delta_time();
            if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
            {
                mPlayer->set_active(true);
                mPlayer->set_visible(true);
                mPlayerHit = false;
                mStars->scroll(true);
            }
        }
        else
        {
            if (mGameOverTimer == 0.0f)
                mPlayer->set_visible(false);

            mGameOverTimer += mTimer->delta_time();
            if (mGameOverTimer >= mGameOverDelay)
            {
                mCurrentState = gameover;
            }
        }
    }
}

void Level::handle_enemy_spawning()
{
    if (InputManager::instance()->key_pressed(SDL_SCANCODE_E))
    {
        mEnemies.push_back(new TIEFighter());
    }
}

Level::LEVEL_STATES Level::get_state()
{
    return mCurrentState;
}

void Level::update()
{
    if (!mStageStarted)
    {
        handle_start_label();
    }
    else
    {
        handle_enemy_spawning();

        for (int i = 0; i < mEnemies.size(); ++i)
        {
            mEnemies[i]->update();
            mEnemies[i]->set_destiny(mPlayer->get_pos(world));
        }

        handle_collisions();

        if (mPlayerHit)
        {
            handle_player_death();
        }
        else
        {
            if (InputManager::instance()->key_pressed(SDL_SCANCODE_N))
                mCurrentState = finished;
        }
    }
}

void Level::render()
{
    if (!mStageStarted)
    {
        if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen)
        {
            mStageLabel->render();
        }
        else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLaeblOffScreen)
        {
            mReadyLabel->render();
        }
    }
    else
    {
        for (int i = 0; i < mEnemies.size(); ++i)
            mEnemies[i]->render();

        if (mPlayerHit)
        {
            if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
                mReadyLabel->render();

            if (mGameOverTimer >= mGameOverLabelOnScreen)
                mGameOverLabel->render();
        }
    }
}



