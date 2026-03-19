#pragma once
#include "../../Core/Object/Object.h"
#include <vector>

class FoodPool;
class Unit;
class Food;

class FoodManager: public Object
{
public:
    FoodManager(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f mapSize);

    void initialize();

    virtual void update(float deltaTime) override;

private:
    std::shared_ptr<FoodPool> foodPool;

    sf::Vector2f mapSize;

    float spawnTimer;

    float spawnInterval;

    void spawnFood();

    bool readyToSpawn;
};