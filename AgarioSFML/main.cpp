#include <memory>
#include "Agario/Game.h"
#include "Core/GameLoop/GameLoop.h"

int main()
{
    auto gameLoop = std::make_shared<GameLoop>(1920, 1080, "AgarioSFML", true);
    gameLoop->initialize();

    auto agarioGame = gameLoop->getFactory()->createObject<Game>();

    gameLoop->runLoop();
}
