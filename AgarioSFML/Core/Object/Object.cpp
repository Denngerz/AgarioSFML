#include "Object.h"
#include "../GameLoop/GameLoop.h"

Object::Object(std::shared_ptr<ObjectFactory> objFactory)
    : isTickable(true),
      isActive(true),
      objectFactory(objFactory)
{
}

void Object::beginPlay()
{
}

const std::shared_ptr<sf::Shape>& Object::getShapeBase() const
{
    static const std::shared_ptr<sf::Shape> Empty{};
    return Empty;
}

bool Object::getIsActive() const
{
    return isActive;
}

void Object::checkCollisionWithObject(std::shared_ptr<Object>& targetObject)
{
    const auto& thisShape = getShapeBase();
    const auto& targetShape = targetObject->getShapeBase();

    if (!thisShape || !targetShape)
    {
        return;
    }

    sf::FloatRect targetBounds = targetShape->getGlobalBounds();
    bool isOverlapping = thisShape->getGlobalBounds().findIntersection(targetBounds).has_value();

    if (isOverlapping)
    {
        onOverlapBegin(targetObject);
    }
}

void Object::onOverlapBegin(std::shared_ptr<Object>& targetCircleObject)
{
}

void Object::update(float deltaTime)
{
}

bool Object::getIsTickable() const
{
    return isTickable;
}

void Object::destroySelf()
{
    isActive = false;
}
