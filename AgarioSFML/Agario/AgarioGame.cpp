#include "AgarioGame.h"
#include <SFML/Graphics.hpp>
#include "../Factory/Factory.h"
#include "AgarioPlayer/AgarioPlayer.h"

AgarioGame::AgarioGame(): GameLoop(1400, 1200, "Agar.io", sf::Color(255, 255, 255, 225)), currentInputEvent(sf::Event::KeyPressed{})
{
}

void AgarioGame::generate()
{
    GameLoop::generate();

    generatePlayer();
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
    player = factory->createObject<AgarioPlayer>(shared_from_this(), 40.0f, sf::Color(225, 0, 225, 225), sf::Vector2f(700, 600));
}
