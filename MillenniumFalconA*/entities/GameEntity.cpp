#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
    mPos.x = x;
    mPos.y = y;

    mRotation = 0.0f;
    mActive = true;
    mParent = nullptr;
    mScale = VEC2_ONE;
}

GameEntity::~GameEntity()
{
    mParent = nullptr;
}

void GameEntity::set_pos(Vector2 pos)
{
    mPos = pos;
}

Vector2 GameEntity::get_pos(SPACE space)
{
    if (space == local || mParent == nullptr)
        return mPos;

    Vector2 parentScale = mParent->get_scale(world);
    Vector2 temp = Vector2((mPos.x * parentScale.x), (mPos.y * parentScale.y));
    Vector2 rot_pos = rotate_vector(temp, mParent->rotation(local));

    return mParent->get_pos(world) + rot_pos;
}

void GameEntity::rotation(float rotation)
{
    mRotation = rotation;

    if(mRotation > 360.0f) {
        int mul = mRotation / 360;
        mRotation -= 360.0f * mul;
    }
    else if(mRotation < 0.0f) {
        int mul = (mRotation / 360) - 1;
        mRotation -= 360.0f * mul;
    }
}

float GameEntity::rotation(SPACE space)
{
    if (space == local || mParent == nullptr)
        return mRotation;

    return mParent->rotation(world) + mRotation;
}

void GameEntity::set_scale(Vector2 scale)
{
    mScale = scale;
}

Vector2 GameEntity::get_scale(SPACE space)
{
    if (space == local || mParent == nullptr)
        return mScale;

    Vector2 scale = mParent->get_scale(world);
    scale.x *= mScale.x;
    scale.y *= mScale.y;

    return scale;
}

void GameEntity::set_active(bool active)
{
    mActive = active;
}

bool GameEntity::is_active()
{
    return mActive;
}

void GameEntity::set_parent(GameEntity *parent)
{
    if (parent == nullptr)
    {
        mPos = get_pos(world);
        mRotation = rotation(world);
        mScale = get_scale(world);
    }
    else
    {
        if (mParent != nullptr)
            set_parent(nullptr);

        Vector2 parentScale = parent->get_scale(world);
        Vector2 temp = get_pos(world) - parent->get_pos(world);
        mPos = rotate_vector(temp, parent->rotation(world));

        mPos.x /= parentScale.x;
        mPos.y /= parentScale.y;

        mRotation -= parent->rotation(world);

        mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
    }

    mParent = parent;
}

GameEntity* GameEntity::get_parent()
{
    return mParent;
}

void GameEntity::translate(Vector2 vec, SPACE space)
{
    if (space == world)
    {
        mPos += vec;
    }
    else
    {
        mPos += rotate_vector(vec, rotation());
    }
}

void GameEntity::rotate(float amount)
{
    mRotation += amount;
}

void GameEntity::update()
{

}

void GameEntity::render()
{

}

