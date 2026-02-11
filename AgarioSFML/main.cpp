#include <memory>
#include "AgarioGame.h"

int main()
{
    auto game = std::make_shared<AgarioGame>();
    game->runLoop();
}