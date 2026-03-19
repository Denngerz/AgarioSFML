#include "FoodPool.h"
#include <ranges>
#include "../../../Core/Utils/HelperFunctions.h"
#include "../../Food/Food.h"

FoodPool::FoodPool(std::shared_ptr<ObjectFactory> objFactory): Object(objFactory)
{
    releaseLocation = sf::Vector2f(10000,10000);
}

void FoodPool::prewarm(int prewarmAmount)
{
    for (int i = 0; i < prewarmAmount; ++i)                                                                                                                                                                                                                                                                       
    {
        auto food = spawnObjectOfClass<Food>(std::dynamic_pointer_cast<FoodPool>(shared_from_this()), 10.0f, HelperFunctions::getRandomColor(), releaseLocation);
        poolMap.emplace(food, false);
    }      
}

std::shared_ptr<Food> FoodPool::getInstance()
{
    auto inactive = poolMap | std::views::filter([](const auto& pair) { return !pair.second; });

    auto count = std::ranges::distance(inactive);
    if (count > 0)
    {
        auto it = inactive.begin();
        std::advance(it, HelperFunctions::getRandomIntInRange(0, static_cast<int>(count) - 1));
        auto& [food, isActive] = *it;
        isActive = true;
        return food;
    }

    return nullptr;
}

void FoodPool::releaseInstance(std::shared_ptr<Food> foodPtr)
{
    auto it = poolMap.find(foodPtr);
    if (it != poolMap.end())
    {
        it->first->getShapeBase()->setPosition(releaseLocation);
        it->first->reset();
        it->second = false;
    }
}
