#include "Food.h"

Food::Food(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor, sf::Vector2f position):
    CircleObject(gameLoop, radius,circleColor, position)
{
}

void Food::becomeEaten()
{
    destroySelf();
}
