#pragma once
#include <memory>
#include <unordered_map>
#include "../../../Core/Object/Object.h"

class Food;

class FoodPool: public Object
{
public:
    FoodPool(std::shared_ptr<ObjectFactory> objFactory);
    
    void prewarm(int prewarmAmount);

    std::shared_ptr<Food> getInstance();

    void releaseInstance(std::shared_ptr<Food> foodPtr);

private:
    std::unordered_map<std::shared_ptr<Food>, bool> poolMap;

    sf::Vector2f releaseLocation;
};
