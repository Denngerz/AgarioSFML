#include "AgarioGame.h"
#include <SFML/Graphics.hpp>
#include "../Factory/Factory.h"
#include "AgarioPlayer/AgarioPlayer.h"
#include "AgarioAI/AgarioAI.h"

AgarioGame::AgarioGame(): GameLoop(1400, 1200, "Agar.io", sf::Color(255, 255, 255, 225)), currentInputEvent(sf::Event::KeyPressed{})
{
}

void AgarioGame::generate()
{
    GameLoop::generate();

    generatePlayer();
    generateEnemies();
}

void AgarioGame::getInput()
{
    GameLoop::getInput();

    while (const std::optional<sf::Event> ev = window->pollEvent())
    {
        currentInputEvent = *ev;
    }
}

void AgarioGame::logic()
{
    player->receiveInput(currentInputEvent); // Нужен инпут менеджер
    
    GameLoop::logic();
}

void AgarioGame::generatePlayer()
{
    player = factory->createObject<AgarioPlayer>(shared_from_this(), 40.0f, sf::Color(225, 0, 0), sf::Vector2f(700, 600));
}

void AgarioGame::generateEnemies()
{
    for (int i = 0; i < 4; ++i)
    {
        std::shared_ptr<AgarioAI> enemy = factory->createObject<AgarioAI>(shared_from_this(), 40.0f, sf::Color(225, 0, 0), sf::Vector2f(700, 600));
        enemies.emplace_back(enemy);
    }
}
