#pragma once
#include "../../Core/Object/Object.h"
#include <vector>

class Unit;
class Food;

class FoodManager: public Object
{
public:
    FoodManager(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f mapSize);

    void update(float deltaTime) override;

    void updateUnits(const std::vector<std::shared_ptr<Unit>>& inUnits);

    void setSpawnRate(float foodPerSecond);

    void setMaxFoodCount(int maxCount);

    int getCurrentFoodCount() const;

private:
    std::vector<std::shared_ptr<Unit>> units;

    std::vector<std::weak_ptr<Food>> spawnedFood;

    sf::Vector2f mapSize;

    float spawnTimer;

    float spawnInterval;

    int maxFoodCount;

    void spawnFood();

    sf::Vector2f getRandomLocation();

    sf::Color getRandomColor();

    bool isInsideAnyUnit(sf::Vector2f position) const;

    void cleanupFoodList();
};