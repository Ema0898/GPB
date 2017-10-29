#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "../tools/MathHelper.h"
#include <iostream>

class GameEntity
{
public:

    enum SPACE
    {
        local = 0, world = 1
    };

private:

    Vector2 mPos;
    float mRotation;
    Vector2 mScale;

    bool mActive;
    GameEntity* mParent;

public:

    GameEntity(float x = 0.0f, float y = 0.0f);
    ~GameEntity();

    void set_pos(Vector2 pos);
    Vector2 get_pos(SPACE space = world);

    void rotation(float rotation);
    float rotation(SPACE space = world);

    void set_scale(Vector2 scale);
    Vector2 get_scale(SPACE space = world);

    void set_active(bool active);
    bool is_active();

    void set_parent(GameEntity* parent);
    GameEntity* get_parent();

    void translate(Vector2 vec, SPACE space = local);
    void rotate(float amount);

    virtual void update();
    virtual void render();
};


#endif //_GAMEENTITIE_H