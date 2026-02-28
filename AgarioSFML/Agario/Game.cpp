#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Player/Player.h"

Game::Game(std::shared_ptr<GameLoop> gameLoop): Object(gameLoop)
{
    currentGameLoop = gameLoop;
}

const std::shared_ptr<sf::Shape>& Game::getShapeBase() const
{
    return Object::getShapeBase();
}

void Game::beginPlay()
{
    Object::beginPlay();

    generatePlayer();
    generateEnemies();
}


void Game::generatePlayer()
{
    player = createObject<Player>(currentGameLoop.lock(), 40, sf::Color(0, 0, 255), sf::Vector2f(700, 600));
}

void Game::generateEnemies()
{
    for (int i = 0; i < 4; ++i)
    {
        std::shared_ptr<Player> enemy = createObject<Player>(currentGameLoop.lock(), 40.0f, sf::Color(225, 0, 0), sf::Vector2f(700, 600), true);
        enemies.emplace_back(enemy);
    }
}
