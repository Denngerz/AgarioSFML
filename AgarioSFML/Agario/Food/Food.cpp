#include "Food.h"

Food::Food(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor, sf::Vector2f position):
    CircleObject(objFactory, radius,circleColor, position)
{
}

void Food::becomeEaten()
{
    destroySelf();
}
