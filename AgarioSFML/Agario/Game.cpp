#include "Game.h"

#include <random>
#include <SFML/Graphics.hpp>

#include "Food/Food.h"
#include "Player/Player.h"

Game::Game(std::shared_ptr<GameLoop> gameLoop)
    : Object(gameLoop),
      spawnTimer(0),
      foodSpawnInterval(0.5)
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

    window = currentGameLoop.lock()->getWindow();
    
    generatePlayer();
    generateEnemies();
}

void Game::update(float deltaTime)
{
    spawnTimer += deltaTime;

    if (spawnTimer >= foodSpawnInterval)
    {
        spawnTimer = 0.0f;
        spawnFood();
    }
}

void Game::onOverlapBegin(std::shared_ptr<Object>& targetObject)
{
}

void Game::generatePlayer()
{
    player = createObject<Player>(currentGameLoop.lock(), 40, sf::Color(0, 0, 255), sf::Vector2f(700, 600));
}

void Game::generateEnemies()
{
    for (int i = 0; i < 4; ++i)
    {
        std::shared_ptr<Player> enemy = createObject<Player>(currentGameLoop.lock(), 20.0f, sf::Color(225, 0, 0), sf::Vector2f(700, 600), true);
        enemies.emplace_back(enemy);
    }
}

void Game::spawnFood()
{
    createObject<Food>(currentGameLoop.lock(), 10, getRandomColor(), getRandomLocation());
}

sf::Vector2f Game::getRandomLocation()
{
    static std::mt19937 randomEngine{ std::random_device{}() };
    
    sf::Vector2u mapSize = window.lock()->getSize();

    std::uniform_real_distribution<float> xDistribution(0, mapSize.x);
    std::uniform_real_distribution<float> yDistribution(0, mapSize.y);

    return sf::Vector2f(xDistribution(randomEngine), yDistribution(randomEngine));
}

sf::Color Game::getRandomColor()
{
    static std::mt19937 randomEngine{ std::random_device{}() };
    static std::uniform_int_distribution<int> colorDistribution(0, 255);

    return sf::Color(
        static_cast<std::uint8_t>(colorDistribution(randomEngine)),
        static_cast<std::uint8_t>(colorDistribution(randomEngine)),
        static_cast<std::uint8_t>(colorDistribution(randomEngine))
    );
}
