#include <memory>
#include "Agario/Game.h"
#include "Core/GameLoop/GameLoop.h"

int main()
{
    auto gameLoop = std::make_shared<GameLoop>(1400, 1200, "AgarioSFML");
    auto agarioGame = createObject<Game>(gameLoop);
    gameLoop->runLoop();
}
