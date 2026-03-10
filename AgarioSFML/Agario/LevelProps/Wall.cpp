#include "Wall.h"

Wall::Wall(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f size, sf::Color color, sf::Vector2f position)
    : Object(objFactory)
{
    rectangleShape = std::make_shared<sf::RectangleShape>(size);
    rectangleShape->setOrigin(size / 2.f);
    rectangleShape->setFillColor(color);
    rectangleShape->setPosition(position);
}

const std::shared_ptr<sf::Shape>& Wall::getShapeBase() const
{
    return rectangleShape;
}

CollisionType Wall::getCollisionResponse() const
{
    return CollisionType::Block;
}