#include "Level.h"

Level::Level(int stage, Player* player)
{
    mTimer = Timer::instance();
    mStars = BackgroundStars::instance();
    audioManager = AudioManager::instance();

    mStage = stage;
    mStageStarted = false;
    mLabelTimer = 0.0f;

    mStageLabel = new Texture("Stage", "Starjedi.ttf", 32, { 75, 75, 200 });
    mStageLabel->set_parent(this);
    mStageLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.5f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mReadyLabel = new Texture("Ready", "Starjedi.ttf", 32, { 150, 0, 0 });
    mReadyLabel->set_parent(this);
    mReadyLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.5f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mGameOverLabel = new Texture("The heroes are safe!", "Starjedi.ttf", 32, { 150, 0, 0 });
    mGameOverLabel->set_parent(this);
    mGameOverLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.5f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mPlayer = player;
    mPlayerDestiny = false;
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

    mRebelBase = new Texture("rebel-base2.png");
    mRebelBase->set_parent(this);
    mRebelBase->set_pos(Vector2(700, 75));

    mCurrentState = running;
}

Level::~Level()
{
    mTimer = nullptr;
    mStars = nullptr;
    audioManager = nullptr;

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

    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        delete mAsteroids[i];
        mAsteroids[i] = nullptr;
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
    if (InputManager::instance()->instance()->key_pressed((SDL_SCANCODE_X)))
    {
        std::cout << "HOLA" << std::endl;
    }

    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        for (int j = 0; j < mAsteroids.size(); ++j)
        {
            if (mAsteroids[i]->collide_with(mAsteroids[j]) && !mAsteroids[i]->same_position(mAsteroids[j]))
            {
                AudioManager::instance()->play_sfx("Explosion4.wav", 0, 1);
                mAsteroids.erase(mAsteroids.begin() + j);
                mAsteroids[i]->move_little();
                mAsteroids.push_back(new Asteroid('s'));
                break;
            }
        }
    }
}

void Level::handle_player_death()
{
    if (!mPlayer->is_animating())
    {
        Vector2 finalPos = Vector2(704, 60);

        if ((int) mPlayer->get_pos(world).x == finalPos.x && (int) mPlayer->get_pos(world).y == finalPos.y)
        {
            if (mGameOverTimer == 0.0f)
            {
                mPlayer->set_visible(false);
                mPlayerDestiny = true;
            }

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
        //mEnemies.push_back(new TIEFighter());
        mAsteroids.push_back(new Asteroid('b'));
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

        for (int i = 0; i < mAsteroids.size(); ++i)
        {
            mAsteroids[i]->update();
        }

        handle_collisions();
        handle_player_death();

        /*if (mPlayerDestiny)
        {
            handle_player_death();
        }
        else
        {
            if (InputManager::instance()->key_pressed(SDL_SCANCODE_N))
                mCurrentState = finished;
        }*/
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

        for (int i = 0; i < mAsteroids.size(); ++i)
        {
            mAsteroids[i]->render();
        }

        mRebelBase->render();

        if (mPlayerDestiny)
        {
            if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
                mReadyLabel->render();

            if (mGameOverTimer >= mGameOverLabelOnScreen)
                mGameOverLabel->render();
        }
    }
}



