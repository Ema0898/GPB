#include "game/Game.h"

int main()
{

    Game* manager = Game::instance();
    manager->run();

    manager->release();
    manager = nullptr;

    return 0;
}