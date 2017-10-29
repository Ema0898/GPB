#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "../entities/AnimatedTexture.h"
#include "../managers/InputManager.h"
#include "../starbackground/BackgroundStars.h"

class StartScreen : public GameEntity
{

private:

    Timer* mTimer;
    InputManager* inputManager;

    // Top Bar Entities
    GameEntity* mTopBar;
    Texture* mPlayerOne;
    Texture* mPlayerTwo;
    Texture* mHighScore;

    // Logo
    Texture* mLogo;
    AnimatedTexture* mAnimatedLogo;

    // Play Mode Entities
    GameEntity* mPlayModes;
    Texture* mOnePlayerMode;
    Texture* mTwoPlayerMode;
    Texture* mCursor;
    Vector2 mCursorStartPos;
    Vector2 mCursorOffset;
    int mSelectedMode;

    // Bottom Bar Entities
    GameEntity* mBotBar;
    Texture* mDates;
    Texture* mRights;

    // Screen Animation
    Vector2 mAnimationStartPos;
    Vector2 mAnimationEndPos;
    float mAnimationTotalTime;
    float mAnimationTimer;
    bool mAnimationDone;

    BackgroundStars* mStars;

public:
    StartScreen();
    ~StartScreen();

    int get_selected_mode();
    void reset_animation();
    void change_selected_mode(int change);
    void update();
    void render();
};


#endif //_STARTSCREEN_H