#include "CircleObject.h"
#include <SFML/Graphics/CircleShape.hpp>

CircleObject::CircleObject(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor, sf::Vector2f position): Object(objFactory)
{
    circleRadius = radius;
    
    circleShape = std::make_shared<sf::CircleShape>(radius);
    circleShape->setOrigin(sf::Vector2f(radius, radius));
    circleShape->setFillColor(circleColor);
    circleShape->setPosition(position);
}

const std::shared_ptr<sf::Shape>& CircleObject::getShapeBase() const
{
    return circleShape;
}

void CircleObject::update(float deltaTime)
{
    Object::update(deltaTime);
}

float CircleObject::getCircleRadius()
{
    return circleRadius;
}

void CircleObject::updateCircleRadius(float newRadius)
{
    auto circleShapePtr = std::dynamic_pointer_cast<sf::CircleShape>(circleShape);
    
    if (circleShapePtr)
    {
        circleRadius = newRadius;
        circleShapePtr->setRadius(circleRadius);
        circleShapePtr->setOrigin(sf::Vector2f(circleRadius, circleRadius));
    }
}
