#include "Object.h"
#include "../Core/GameLoop.h"

void Object::initializeObject()
{
}

const std::shared_ptr<sf::Shape>& Object::getShapeBase() const
{
    return shapeBase;
}

void Object::destroySelf()
{
    if (auto gl = currentGameLoop.lock())
    {
        gl->removeUpdatableShape(shapeBase);
    }
}

void Object::setShapeBase(std::shared_ptr<sf::Shape>& newShape)
{
    shapeBase = std::move(newShape);
}
