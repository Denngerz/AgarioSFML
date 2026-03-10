#pragma once

#include "../../Core/Object/Object.h"
#include "../../Core/Interfaces/ICollidable.h"

class Wall : public Object, public ICollidable
{
public:
    Wall(std::shared_ptr<ObjectFactory> objFactory, sf::Vector2f size, sf::Color color, sf::Vector2f position);

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    CollisionType getCollisionResponse() const override;

private:
    std::shared_ptr<sf::Shape> rectangleShape;
};