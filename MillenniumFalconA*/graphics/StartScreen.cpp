#include "StartScreen.h"

StartScreen::StartScreen()
{
    mTimer = Timer::instance();
    inputManager = InputManager::instance();

    // Top Bar Entities
    mTopBar = new GameEntity(Graphics::instance()->SCREEN_WIDTH / 2, 80.0f);
    mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mHighScore = new Texture("HI-SCORE", "emulogic.ttf", 32, { 200, 0, 0 });


    mPlayerOne->set_parent(mTopBar);
    mPlayerTwo->set_parent(mTopBar);
    mHighScore->set_parent(mTopBar);

    mPlayerOne->set_pos(Vector2(-Graphics::instance()->SCREEN_WIDTH * 0.35f, -30.0f));
    mPlayerTwo->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH * 0.2f, -30.0f));
    mHighScore->set_pos(Vector2(-30.0f, -30.0f));

    mTopBar->set_parent(this);

    //Logo
    mLogo = new Texture("logo.png", 0, 0, 489, 145);
    mLogo->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH / 2, Graphics::instance()->SCREEN_HEIGHT * 0.40f));
    mLogo->set_parent(this);


    mAnimatedLogo = new AnimatedTexture("logoanimado.png", 0, 0, 360, 81, 3, 0.2f, AnimatedTexture::vertical);
    mAnimatedLogo->set_pos(Vector2(Graphics::instance()->SCREEN_WIDTH / 2, Graphics::instance()->SCREEN_HEIGHT * 0.40f));
    mAnimatedLogo->set_parent(this);

    //Play Mode Entities
    mPlayModes = new GameEntity(Graphics::instance()->SCREEN_WIDTH / 2, Graphics::instance()->SCREEN_HEIGHT * 0.55f);
    mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230, 230, 230 });
    mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
    mCursor = new Texture("cursor.png");

    mOnePlayerMode->set_parent(mPlayModes);
    mTwoPlayerMode->set_parent(mPlayModes);
    mCursor->set_parent(mPlayModes);

    mOnePlayerMode->set_pos(Vector2(-20.0f, -0.5f));
    mTwoPlayerMode->set_pos(Vector2(0.0f, 60.0f));
    mCursor->set_pos(Vector2(-190.0f, -0.5f));

    mPlayModes->set_parent(this);

    mCursorStartPos = mCursor->get_pos(local);
    mCursorOffset = Vector2(0.0f, 70.0f);
    mSelectedMode = 0;

    // Bottom Bar Entities
    mBotBar = new GameEntity(Graphics::instance()->SCREEN_WIDTH / 2, Graphics::instance()->SCREEN_HEIGHT * 0.7f);
    mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
    mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

    mDates->set_parent(mBotBar);
    mRights->set_parent(mBotBar);

    mDates->set_pos(Vector2(0.0f, 100.0f));
    mRights->set_pos(Vector2(0.0f, 150.0f));

    mBotBar->set_parent(this);

    // Screen Animation
    reset_animation();

    mStars = BackgroundStars::instance();
    mStars->scroll(true);
}

StartScreen::~StartScreen()
{
    // Top bar entities
    delete mTopBar;
    mTopBar = nullptr;
    delete mPlayerOne;
    mPlayerOne = nullptr;
    delete mPlayerTwo;
    mPlayerTwo = nullptr;
    delete mHighScore;
    mHighScore = nullptr;

    // Logo
    delete mLogo;
    mLogo = nullptr;
    delete mAnimatedLogo;
    mAnimatedLogo = nullptr;

    // Play Mode Entities
    delete mPlayModes;
    mPlayModes = nullptr;
    delete mOnePlayerMode;
    mOnePlayerMode = nullptr;
    delete mTwoPlayerMode;
    mTwoPlayerMode = nullptr;
    delete mCursor;
    mCursor = nullptr;

    // Bottom Bar Entities
    delete mBotBar;
    mBotBar = nullptr;
    delete mDates;
    mDates = nullptr;
    delete mRights;
    mRights = nullptr;
}

void StartScreen::reset_animation()
{
    mAnimationStartPos = Vector2(0.0f, Graphics::instance()->SCREEN_WIDTH);
    mAnimationEndPos = Vector2(0.0f, 0.0f);
    mAnimationTotalTime = 5.0f;
    mAnimationTimer = 0.0f;
    mAnimationDone = false;

    set_pos(mAnimationStartPos);
}

int StartScreen::get_selected_mode()
{
    return mSelectedMode;
}

void StartScreen::change_selected_mode(int change)
{
    mSelectedMode += change;

    if (mSelectedMode < 0)
        mSelectedMode = 1;

    else if (mSelectedMode > 1)
        mSelectedMode = 0;

    mCursor->set_pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::update()
{
    if (!mAnimationDone)
    {
        mAnimationTimer += mTimer->delta_time();
        set_pos(lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

        if (mAnimationTimer >= mAnimationTotalTime)
        {
            mAnimationDone = true;
            mStars->scroll(false);
        }

        if (inputManager->key_pressed(SDL_SCANCODE_DOWN) || inputManager->key_pressed(SDL_SCANCODE_UP))
            mAnimationTimer = mAnimationTotalTime;
    }
    else
    {
        mAnimatedLogo->update();

        if (inputManager->key_pressed(SDL_SCANCODE_DOWN))
            change_selected_mode(1);
        else if (inputManager->key_pressed(SDL_SCANCODE_UP))
            change_selected_mode(-1);
    }

}

void StartScreen::render()
{
    mPlayerOne->render();
    mPlayerTwo->render();
    mHighScore->render();

    if (!mAnimationDone)
        mLogo->render();
    else
        mAnimatedLogo->render();

    mOnePlayerMode->render();
    mTwoPlayerMode->render();
    mCursor->render();

    mDates->render();
    mRights->render();
}
