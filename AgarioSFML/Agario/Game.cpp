#include "Game.h"
#include <random>
#include <SFML/Graphics.hpp>
#include "Food/Food.h"
#include "Controllers/PlayerController.h"
#include "CirclePawn/Unit.h"
#include "LevelProps/Wall.h"
#include "../Core/Utils/HelperFunctions.h"
#include "../Core/World/World.h"

Game::Game(std::shared_ptr<ObjectFactory> objectFactory)
    : Object(objectFactory),
      spawnTimer(0),
      foodSpawnInterval(0.5)
{
    mapSize = sf::Vector2f(2000.0f, 2000.0f);
}

const std::shared_ptr<sf::Shape>& Game::getShapeBase() const
{
    return Object::getShapeBase();
}

void Game::beginPlay()
{
    Object::beginPlay();

    generateWalls();
    generateUnits();
    generatePlayer();
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

std::shared_ptr<Unit> Game::getRandomUnit(std::shared_ptr<Unit> exeptionUnit) const
{
    std::vector<std::shared_ptr<Unit>> aliveUnits;

    for (const auto& unit : units)
    {
        if (unit && unit->getIsActive() && unit != exeptionUnit)
        {
            aliveUnits.emplace_back(unit);
        }
    }

    if (aliveUnits.empty())
    {
        return nullptr;
    }

    return aliveUnits[HelperFunctions::getRandomIntInRange(0, static_cast<int>(aliveUnits.size()) - 1)];
}

void Game::generateWalls()
{
    walls.emplace_back(spawnObjectOfClass<Wall>(sf::Vector2f(40, 4000), sf::Color(0, 0, 0), currentWorld->sfmlToWorld(sf::Vector2f(2000, 0))));
    walls.emplace_back(spawnObjectOfClass<Wall>(sf::Vector2f(4000, 40), sf::Color(0, 0, 0), currentWorld->sfmlToWorld(sf::Vector2f(0, -2000))));
    walls.emplace_back(spawnObjectOfClass<Wall>(sf::Vector2f(40, 4000), sf::Color(0, 0, 0), currentWorld->sfmlToWorld(sf::Vector2f(-2000, 0))));
    walls.emplace_back(spawnObjectOfClass<Wall>(sf::Vector2f(4000, 40), sf::Color(0, 0, 0), currentWorld->sfmlToWorld(sf::Vector2f(0, 2000))));
}

void Game::generatePlayer()
{
    playerController = spawnObjectOfClass<PlayerController>();
    playerController->setGamemode(std::static_pointer_cast<Game>(shared_from_this()));
    playerController->possessPawn(std::dynamic_pointer_cast<Pawn>(getRandomUnit()));
}

void Game::generateUnits()
{
    for (int i = 0; i < 5; ++i)
    {
        std::shared_ptr<Unit> unit = spawnObjectOfClass<Unit>(20.0f, sf::Color(225, 0, 0), getRandomLocation(), true);
        units.emplace_back(unit);
    }
}

void Game::spawnFood()
{
    spawnObjectOfClass<Food>(10, getRandomColor(), getRandomLocation());
}

sf::Vector2f Game::getRandomLocation()
{
    static std::mt19937 randomEngine{ std::random_device{}() };

    float maxX = mapSize.x - 100;
    float maxY = mapSize.y - 100;
    
    std::uniform_real_distribution<float> xDistribution(-maxX, maxX);
    std::uniform_real_distribution<float> yDistribution(-maxY, maxY);

    sf::Vector2f location = currentWorld->sfmlToWorld(sf::Vector2f(xDistribution(randomEngine), yDistribution(randomEngine)));

    return location;
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
