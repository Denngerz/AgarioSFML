#include "AgarioGame.h"
#include <SFML/Graphics.hpp>

#include "Factory/Factory.h"
#include "Object/CircleObject/CircleObject.h"

AgarioGame::AgarioGame(): GameLoop(1400, 1200, "Agar.io", sf::Color(255,255,255,225))
{
}

void AgarioGame::generate()
{
    GameLoop::generate();

    generatePlayers();
}

void AgarioGame::generatePlayers()
{
    std::shared_ptr player1 = factory->createObject<CircleObject>(shared_from_this(), 40.0f, sf::Color(225, 0, 225, 225), sf::Vector2f(50, 50));
}
