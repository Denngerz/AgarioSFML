#include "Game.h"
#include <random>
#include <ranges>
#include <SFML/Graphics.hpp>
#include "Controllers/PlayerController.h"
#include "CirclePawn/Unit.h"
#include "LevelProps/Wall.h"
#include "FoodManager/FoodManager.h"
#include "../Core/Utils/HelperFunctions.h"
#include "../Core/World/World.h"

Game::Game(std::shared_ptr<ObjectFactory> objectFactory)
    : Object(objectFactory)
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

    foodManager = spawnObjectOfClass<FoodManager>(mapSize);
    foodManager->updateUnits(units);
}

void Game::update(float deltaTime)
{
    if (foodManager)
    {
        foodManager->updateUnits(units);
    }
}

std::shared_ptr<Unit> Game::getRandomUnit(std::shared_ptr<Unit> exeptionUnit) const
{
    auto aliveUnits = units | std::views::filter([&exeptionUnit](const auto& unit) {
        return unit && unit->getIsActive() && unit != exeptionUnit;
    });

    auto count = std::ranges::distance(aliveUnits);

    if (count == 0)
    {
        return nullptr;
    }

    auto it = aliveUnits.begin();
    std::advance(it, HelperFunctions::getRandomIntInRange(0, static_cast<int>(count) - 1));

    return *it;
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
    static std::mt19937 randomEngine{ std::random_device{}() };

    float maxX = mapSize.x - 100;
    float maxY = mapSize.y - 100;

    std::uniform_real_distribution<float> xDistribution(-maxX, maxX);
    std::uniform_real_distribution<float> yDistribution(-maxY, maxY);

    for (int i = 0; i < 5; ++i)
    {
        sf::Vector2f location = currentWorld->sfmlToWorld(sf::Vector2f(xDistribution(randomEngine), yDistribution(randomEngine)));
        std::shared_ptr<Unit> unit = spawnObjectOfClass<Unit>(20.0f, sf::Color(225, 0, 0), location, true);
        units.emplace_back(unit);
    }
}
