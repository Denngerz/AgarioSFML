#include "Food.h"

Food::Food(std::shared_ptr<ObjectFactory> objFactory,float radius, sf::Color circleColor, sf::Vector2f position)
    :Object(objFactory),
    circleRadius(radius)
{
    circleRadius = radius;
    
    circleShape = std::make_shared<sf::CircleShape>(radius);
    circleShape->setOrigin(sf::Vector2f(radius, radius));
    circleShape->setFillColor(circleColor);
    circleShape->setPosition(position);
}

void Food::becomeEaten()
{
    destroySelf();
}

float Food::getRadius()
{
    return circleRadius;
}

sf::Vector2f Food::getPosition()
{
    return circleShape->getPosition();
}

const std::shared_ptr<sf::Shape>& Food::getShapeBase() const
{
    return circleShape;
}
