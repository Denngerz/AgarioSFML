#include "FoodManager.h"
#include <algorithm>
#include <random>
#include <ranges>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Food/Food.h"
#include "../CirclePawn/Unit.h"
#include "../../Core/World/World.h"

FoodManager::FoodManager(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f mapSize)
    : Object(objFactory),
      mapSize(mapSize),
      spawnTimer(0),
      spawnInterval(0.5f),
      maxFoodCount(200)
{
}

void FoodManager::update(float deltaTime)
{
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.0f;

        if (getCurrentFoodCount() < maxFoodCount)
        {
            spawnFood();
        }
    }
}

void FoodManager::updateUnits(const std::vector<std::shared_ptr<Unit>>& inUnits)
{
    units = inUnits;
}

void FoodManager::setSpawnRate(float foodPerSecond)
{
    if (foodPerSecond > 0.0f)
    {
        spawnInterval = 1.0f / foodPerSecond;
    }
}

void FoodManager::setMaxFoodCount(int maxCount)
{
    maxFoodCount = maxCount;
}

int FoodManager::getCurrentFoodCount() const
{
    return static_cast<int>(std::ranges::count_if(spawnedFood, [](const auto& weakFood) {
        auto food = weakFood.lock();
        return food && food->getIsActive();
    }));
}

void FoodManager::spawnFood()
{
    cleanupFoodList();

    constexpr int maxAttempts = 10;
    sf::Vector2f location;

    for (int i = 0; i < maxAttempts; ++i)
    {
        location = getRandomLocation();

        if (!isInsideAnyUnit(location))
        {
            auto food = spawnObjectOfClass<Food>(10, getRandomColor(), location);
            spawnedFood.emplace_back(food);
            return;
        }
    }

    auto food = spawnObjectOfClass<Food>(10, getRandomColor(), location);
    spawnedFood.emplace_back(food);
}

sf::Vector2f FoodManager::getRandomLocation()
{
    static std::mt19937 randomEngine{ std::random_device{}() };

    float maxX = mapSize.x - 100;
    float maxY = mapSize.y - 100;

    std::uniform_real_distribution<float> xDistribution(-maxX, maxX);
    std::uniform_real_distribution<float> yDistribution(-maxY, maxY);

    sf::Vector2f location = currentWorld->sfmlToWorld(sf::Vector2f(xDistribution(randomEngine), yDistribution(randomEngine)));

    return location;
}

sf::Color FoodManager::getRandomColor()
{
    static std::mt19937 randomEngine{ std::random_device{}() };
    static std::uniform_int_distribution<int> colorDistribution(0, 255);

    return sf::Color(
        static_cast<std::uint8_t>(colorDistribution(randomEngine)),
        static_cast<std::uint8_t>(colorDistribution(randomEngine)),
        static_cast<std::uint8_t>(colorDistribution(randomEngine))
    );
}

bool FoodManager::isInsideAnyUnit(sf::Vector2f position) const
{
    auto activeUnits = units | std::views::filter([](const auto& unit) { return unit && unit->getIsActive(); });

    return std::ranges::any_of(activeUnits, [&position](const auto& unit) {
        sf::Vector2f unitPos = unit->getPosition();
        float radius = unit->getCircleRadius();
        float dx = position.x - unitPos.x;
        float dy = position.y - unitPos.y;
        return dx * dx + dy * dy < radius * radius;
    });
}

void FoodManager::cleanupFoodList()
{
    for (int i = static_cast<int>(spawnedFood.size()) - 1; i >= 0; --i)
    {
        if (spawnedFood[i].expired())
        {
            std::swap(spawnedFood[i], spawnedFood.back());
            spawnedFood.pop_back();
        }
    }
}