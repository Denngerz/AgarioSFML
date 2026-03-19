#include "FoodManager.h"

#include "../../Core/Components/CameraComponent.h"
#include "../../Core/Utils/HelperFunctions.h"
#include "../Food/Food.h"
#include "../Pools/FoodPool/FoodPool.h"

FoodManager::FoodManager(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f mapSize)
    : Object(objFactory),
    mapSize(mapSize),
    spawnInterval(0.5f),
    spawnTimer(0.0f),
    readyToSpawn(false)
{
}

void FoodManager::initialize()
{
    foodPool = spawnObjectOfClass<FoodPool>();

    foodPool->prewarm(200);

    readyToSpawn = true;
}

void FoodManager::update(float deltaTime)
{
    Object::update(deltaTime);

    if (!readyToSpawn)
    {
        return;
    }
    
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.0f;
        spawnFood();
    }
}

void FoodManager::spawnFood()
{
    auto food = foodPool->getInstance();

    if (!food)
    {
        return;
    }

    int maxX = static_cast<int>(mapSize.x) - 10;
    int maxY = static_cast<int>(mapSize.y) - 10;
    food->getShapeBase()->setPosition(sf::Vector2f(static_cast<float>(HelperFunctions::getRandomIntInRange(-maxX, maxX)), static_cast<float>(HelperFunctions::getRandomIntInRange(-maxY, maxY))));
}
