#include "Asteroid.h"

Asteroid::Asteroid(char size)
{
    mTimer = Timer::instance();
    grid = Grid::instance();

    if (size == 'b')
    {
        mTexture = new Texture("meteorBrown_med1.png");
    }
    else if (size == 's')
    {
        mTexture = new Texture("meteorBrown_small2.png");
    }

    mTexture->set_parent(this);
    mTexture->set_pos(VEC2_ZERO);

    mSpeed = 150.0f;

    set_pos(Vector2(rand() % Graphics::instance()->SCREEN_WIDTH, 0.0f));
    //set_pos(Vector2(320, 0.0f));
}

Asteroid::~Asteroid()
{
    mTimer = nullptr;
    grid = nullptr;

    delete mTexture;
    mTexture = nullptr;
}

bool Asteroid::same_position(Asteroid *asteroid)
{
    Vector2 pos = get_pos(local);

    if (pos.x == asteroid->get_pos().x && pos.y == asteroid->get_pos().y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Asteroid::move_little()
{
    Vector2 pos = get_pos(local);
    set_pos(Vector2(pos.x + 50, pos.y + 50));
}

void Asteroid::handle_movement()
{
    translate(VEC2_UP * mSpeed * mTimer->delta_time(), world);

    Vector2 pos = get_pos(local);

    if (pos.y > Graphics::instance()->SCREEN_HEIGHT)
    {
        pos.y = 0.0f;
        pos.x = rand() % Graphics::instance()->SCREEN_WIDTH;
        set_pos(pos);
    }

    grid->set_matrix_pos((int) (pos.x / 32), (int) (pos.y / 32));
}

bool Asteroid::collide_with(Asteroid *asteroid)
{
    Vector2 targetPos = asteroid->get_pos(world);
    Vector2 currentPos = get_pos(world);

    if (currentPos.y >= targetPos.y + 32)
    {
        return false;
    }
    if (currentPos.x >= targetPos.x + 32)
    {
        return false;
    }
    if (currentPos.y + 32 <= targetPos.y)
    {
        return false;
    }
    if (currentPos.x + 32 <= targetPos.x)
    {
        return false;
    }

    return true;
}

void Asteroid::update()
{
    handle_movement();
}

void Asteroid::render()
{
    mTexture->render();
}
