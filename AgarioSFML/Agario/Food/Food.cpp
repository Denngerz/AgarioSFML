#include "Food.h"

Food::Food(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor, sf::Vector2f position):
    CircleObject(gameLoop, radius,circleColor, position)
{
}

void Food::getEaten()
{
    destroySelf();
}

void Food::onOverlapBegin(std::shared_ptr<Object>& targetObject)
{
}
