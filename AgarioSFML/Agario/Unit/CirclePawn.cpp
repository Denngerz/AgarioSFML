#include "CirclePawn.h"

CirclePawn::CirclePawn(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor,sf::Vector2f position)
    : Pawn(objFactory)
{
    circleRadius = radius;
    
    circleShape = std::make_shared<sf::CircleShape>(radius);
    circleShape->setOrigin(sf::Vector2f(radius, radius));
    circleShape->setFillColor(circleColor);
    circleShape->setPosition(position);
}

const std::shared_ptr<sf::Shape>& CirclePawn::getShapeBase() const
{
    return circleShape;
}

void CirclePawn::update(float deltaTime)
{
    Object::update(deltaTime);
}

float CirclePawn::getCircleRadius()
{
    return circleRadius;
}

void CirclePawn::beginPlay()
{
    Object::beginPlay();
}

void CirclePawn::updateCircleRadius(float newRadius)
{
    auto circleShapePtr = std::dynamic_pointer_cast<sf::CircleShape>(circleShape);
    
    if (circleShapePtr)
    {
        circleRadius = newRadius;
        circleShapePtr->setRadius(circleRadius);
        circleShapePtr->setOrigin(sf::Vector2f(circleRadius, circleRadius));
    }
}