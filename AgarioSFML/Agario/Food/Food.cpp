#include "Food.h"
#include <corecrt_math_defines.h>

Food::Food(std::shared_ptr<ObjectFactory> objFactory,float radius, sf::Color circleColor, sf::Vector2f position)
    :Object(objFactory),
    circleRadius(radius)
{
    circleRadius = radius;
    
    circleShape = std::make_shared<sf::CircleShape>(radius);
    circleShape->setOrigin(sf::Vector2f(radius, radius));
    circleShape->setFillColor(circleColor);
    circleShape->setPosition(position);

    collisionResponse = CollisionType::Overlap;
}

void Food::becomeEaten()
{
    destroySelf();
}

float Food::getArea()
{
    return M_PI * pow(circleRadius, 2);
}

sf::Vector2f Food::getPosition()
{
    return circleShape->getPosition();
}

CollisionType Food::getCollisionResponse() const
{
    return collisionResponse;
}

const std::shared_ptr<sf::Shape>& Food::getShapeBase() const
{
    return circleShape;
}
