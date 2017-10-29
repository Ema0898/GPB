#include "TIEFighter.h"

TIEFighter::TIEFighter()
{
    grid = Grid::instance();
    aStar = new AStar();

    mTimer = Timer::instance();

    mTexture = nullptr;
    mSpeed = 100.0f;

    mMoveBounds = Vector2(30.0f, 800.0f);

    mTexture = new Texture("butterfly.png");
    mTexture->set_parent(this);
    mTexture->set_pos(VEC2_ZERO);

    mDestiny = Vector2(18.0f, 24.0f);

    this->set_pos(Vector2(300.0f, 150.0f));
}

TIEFighter::~TIEFighter()
{
    grid = nullptr;

    delete aStar;
    aStar = nullptr;

    mTimer = nullptr;

    delete mTexture;
    mTexture = nullptr;
}

void TIEFighter::handle_movement()
{
    Vector2 pos1 = get_pos(world);
    Pair current_pos = std::make_pair((int) (pos1.y / 32), (int) (pos1.x / 32));
    Pair current_des = std::make_pair((int) mDestiny.y / 32, (int) mDestiny.x / 32);

    /*aStar->aStarSearch(grid->get_matrix(), current_pos, current_des);
    Pair delta = aStar->getCell();

    if (delta.first < current_pos.first && delta.second == current_pos.second)
    {
        translate(-VEC2_UP * mSpeed * mTimer->delta_time(), world);
        grid->set_matrix_pos(current_pos.second, current_pos.first, 0);
    }
    else if (delta.first > current_pos.first && delta.second == current_pos.second)
    {
        translate(VEC2_UP * mSpeed * mTimer->delta_time(), world);
        grid->set_matrix_pos(current_pos.second, current_pos.first, 0);
    }
    else if (delta.second > current_pos.second && delta.first == current_pos.first)
    {
        translate(VEC2_RIGHT * mSpeed * mTimer->delta_time(), world);
        grid->set_matrix_pos(current_pos.second, current_pos.first, 0);
    }
    else if (delta.second < current_pos.second && delta.first == current_pos.first)
    {
        translate(-VEC2_RIGHT * mSpeed * mTimer->delta_time(), world);
        grid->set_matrix_pos(current_pos.second, current_pos.first, 0);
    }
    */

    grid->set_matrix_pos(current_pos.second, current_pos.first, 0);
    Vector2 pos = get_pos(local);
    if (pos.x < mMoveBounds.x)
        pos.x = mMoveBounds.x;
    else if (pos.x > mMoveBounds.y)
        pos.x = mMoveBounds.y;
    set_pos(pos);
}

void TIEFighter::set_destiny(Vector2 destiny)
{
    mDestiny = destiny;
}

void TIEFighter::update()
{
    if (is_active())
    {
        handle_movement();
    }
}

void TIEFighter::render()
{
    if (is_active())
    {
        mTexture->render();
    }
}