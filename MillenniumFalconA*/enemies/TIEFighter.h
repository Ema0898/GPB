#ifndef _TIEFIGHTER_H
#define _TIEFIGHTER_H

#include "../pathfinding/Grid.h"
#include "../pathfinding/AStar.h"
#include "../entities/GameEntity.h"
#include "../tools/Timer.h"
#include "../entities/Texture.h"

class TIEFighter : public GameEntity
{
private:
    AStar* aStar;
    Grid* grid;
    Timer* mTimer;
    Texture* mTexture;

    float mSpeed;

    Vector2 mMoveBounds;
    Vector2 mDestiny;

private:
    void handle_movement();

public:
    TIEFighter();
    ~TIEFighter();

    void set_destiny(Vector2 destiny);

    void update();
    void render();
};


#endif //_TIEFIGHTER_H
