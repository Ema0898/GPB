#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "../entities/GameEntity.h"
#include "../entities/Texture.h"
#include "../entities/AnimatedTexture.h"
#include "../pathfinding/Grid.h"
#include "../tools/Timer.h"

class Asteroid : public GameEntity
{
private:
    Grid* grid;
    Timer* mTimer;

    Texture* mTexture;

    float mSpeed;

private:
    void handle_movement();

public:
    Asteroid(char size);
    ~Asteroid();

    bool collide_with(Asteroid* asteroid);
    bool same_position(Asteroid* asteroid);
    void move_little();

    void update();
    void render();
};


#endif //_ASTEROID_H
