#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
    mTimer = Timer::instance();
    inputManager = InputManager::instance();
    audioManager = AudioManager::instance();
    mStars = BackgroundStars::instance();

    mStartLabel = new Texture("Start", "emulogic.ttf", 32, { 150, 0, 0 });
    mStartLabel->set_parent(this);
    mStartLabel->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.4f, Graphics::instance()->SCREEN_HEIGHT * 0.5f));

    mLevel = nullptr;

    mPlayer = nullptr;

    mLevelStartDelay = 0.5f;
    mLevelStarted = false;
}

PlayScreen::~PlayScreen()
{
    mTimer = nullptr;
    inputManager = nullptr;
    mStars = nullptr;

    delete mStartLabel;
    mStartLabel = nullptr;

    delete mLevel;
    mLevel = nullptr;

    delete mPlayer;
    mPlayer = nullptr;
}

void PlayScreen::start_next_level()
{
    mCurrentStage++;
    mLevelStartTimer = 0.0f;
    mLevelStarted = true;

    delete mLevel;
    mLevel =  new Level(mCurrentStage, mPlayer);
}

void PlayScreen::start_new_game()
{
    delete mPlayer;
    mPlayer = new Player();
    mPlayer->set_parent(this);
    mPlayer->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.4f, Graphics::instance()->SCREEN_HEIGHT * 0.9f));
    mPlayer->set_active(false);

    mStars->scroll(false);

    mGameStarted = false;
    mLevelStarted = false;
    mLevelStartTimer = 0.0f;

    audioManager->play_music("galaga.wav", 0);
    mCurrentStage = 0;
}

bool PlayScreen::game_over()
{
    if (!mLevelStarted)
        return false;

    return (mLevel->get_state() == Level::gameover);
}

void PlayScreen::update()
{
    if (mGameStarted)
    {
        if (!mLevelStarted)
        {
            mLevelStartTimer += mTimer->delta_time();
            if (mLevelStartTimer >= mLevelStartDelay)
            {
                std::cout << "LEVEL STARTED" << std::endl;
                start_next_level();
            }

        }
    }
    else
    {
        if (!Mix_PlayingMusic())
        {
            mGameStarted = true;
        }
    }

    if (mGameStarted)
    {

        if (mLevelStarted)
        {
            mLevel->update();

            if (mLevel->get_state() == Level::finished)
            {
                mLevelStarted = false;
            }
        }

        mPlayer->update();
    }
}

void PlayScreen::render()
{

    if (!mGameStarted)
        mStartLabel->render();

    if (mGameStarted)
    {
        if (mLevelStarted)
            mLevel->render();

        mPlayer->render();
    }
}

