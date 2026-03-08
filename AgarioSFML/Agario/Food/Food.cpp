#include "Food.h"

Food::Food(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input, float radius, sf::Color circleColor, sf::Vector2f position):
    CircleObject(objFactory, input, radius,circleColor, position)
{
}

void Food::becomeEaten()
{
    destroySelf();
}
