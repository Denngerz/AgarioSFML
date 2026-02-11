#include "CircleObject.h"
#include <SFML/Graphics/CircleShape.hpp>

CircleObject::CircleObject(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor, sf::Vector2f position): Object(gameLoop)
{
    circleShape = std::make_shared<sf::CircleShape>(radius);
    circleShape->setOrigin(sf::Vector2f(radius, radius));
    circleShape->setFillColor(circleColor);
    circleShape->setPosition(position);
}

void CircleObject::initializeObject()
{
    Object::initializeObject();
    
    setShapeBase(circleShape);
}
