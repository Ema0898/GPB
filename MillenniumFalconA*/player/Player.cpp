#include "Player.h"

Player::Player()
{
    mTimer = Timer::instance();
    inputManager = InputManager::instance();
    audioManager = AudioManager::instance();
    grid = Grid::instance();

    aStar = new AStar();

    mShip = new Texture("millennium_falcon2.png");
    mShip->set_parent(this);
    mShip->set_pos(VEC2_ZERO);
    mShip->set_scale(Vector2(3.0f, 3.0f));

    mVisible = false;
    mAnimating = false;
    mScore = 0;
    mLives = 2;
    mMoveSpeed = 200.0f;

    mMoveBounds = Vector2(30.0f, 800.0f);
    mDestiny = Vector2(0, 15);

    mDeathAnimation = new AnimatedTexture("SpriteSheet.png", 250, 47, 32, 32, 4, 1.0f, AnimatedTexture::horizontal);
    mDeathAnimation->set_parent(this);
    mDeathAnimation->set_pos(VEC2_ZERO);
    mDeathAnimation->set_wrap_mode(AnimatedTexture::once);
}

Player::~Player()
{
    mTimer = nullptr;
    inputManager = nullptr;
    audioManager = nullptr;
    grid = nullptr;

    delete mShip;
    mShip = nullptr;

    delete mDeathAnimation;
    mDeathAnimation = nullptr;

    delete aStar;
    aStar = nullptr;
}

void Player::handle_movement()
{
    Vector2 pos1 = get_pos(world);
    Pair current_pos = std::make_pair((int) (pos1.y / 32), (int) (pos1.x / 32));
    Pair current_des = std::make_pair((int) mDestiny.x, (int) mDestiny.y);

    aStar->aStarSearch(grid->get_matrix(), current_pos, current_des);
    Pair delta = aStar->getCell();

    if (delta.first < current_pos.first && delta.second == current_pos.second)
    {
        translate(-VEC2_UP * mMoveSpeed * mTimer->delta_time(), world);
    }
    else if (delta.first > current_pos.first && delta.second == current_pos.second)
    {
        translate(VEC2_UP * mMoveSpeed * mTimer->delta_time(), world);
    }
    else if (delta.second > current_pos.second && delta.first == current_pos.first)
    {
        translate(VEC2_RIGHT * mMoveSpeed * mTimer->delta_time(), world);
    }
    else if (delta.second < current_pos.second && delta.first == current_pos.first)
    {
        translate(-VEC2_RIGHT * mMoveSpeed * mTimer->delta_time(), world);
    }
    else if (inputManager->key_pressed((SDL_SCANCODE_Q)))
    {
        std::cout << "//////////////////////////////" << std::endl;
        grid->print_matrix();
    }

    Vector2 pos = get_pos(local);
    if (pos.x < mMoveBounds.x)
        pos.x = mMoveBounds.x;
    else if (pos.x > mMoveBounds.y)
        pos.x = mMoveBounds.y;
    set_pos(pos);
}

void Player::set_visible(bool visible)
{
    mVisible = visible;
}

bool Player::is_animating()
{
    return mAnimating;
}

int Player::get_score()
{
    return mScore;
}

int Player::get_lives()
{
    return mLives;
}

void Player::add_score(int change)
{
    mScore += change;
}

void Player::was_hit()
{
    mLives--;
    mDeathAnimation->reset_animation();
    mAnimating = true;
    audioManager->play_sfx("Explosion4.wav");
}

void Player::update()
{
    if (mAnimating)
    {
        mDeathAnimation->update();
        mAnimating = mDeathAnimation->is_animating();
    }
    else
    {
        if (is_active())
        {
            handle_movement();
        }
    }
}

void Player::render()
{
    if (mVisible)
    {
        if (mAnimating)
        {
            mDeathAnimation->render();
        }
        else
        {
            mShip->render();
        }
    }
}


