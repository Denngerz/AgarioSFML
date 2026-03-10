#include "Unit.h"
#include <random>

#include "../../Core/Components/CameraComponent.h"
#include "../../Core/GameLoop/GameLoop.h"
#include "../../Core/Utils/HelperFunctions.h"
#include "../../Core/Controller/Controller.h"

Unit::Unit(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor,sf::Vector2f position, bool isAI)
    : CirclePawn(objFactory, radius, circleColor, position),
      speed(200),
      lastDeltaTime(0),
      hasReachedTargetLocation(true)
{
    isAIControlled = isAI;

    collisionType = CollisionType::Overlap;

    cameraComponent = std::make_shared<CameraComponent>(sf::Vector2f(0.0f, 0.0f), 0.5f);
}

void Unit::update(float deltaTime)
{
    CirclePawn::update(deltaTime);

    lastDeltaTime = deltaTime;
    
    if (isAIControlled)
    {
        tryChooseRandomTargetPos();
        tryMoveToTargetPos(deltaTime);
    }
}

void Unit::becomeEaten()
{
    
    destroySelf();
}

float Unit::getRadius()
{
    return circleRadius;
}

sf::Vector2f Unit::getPosition()
{
    return circleShape->getPosition();
}

std::shared_ptr<CameraComponent> Unit::getCameraComponent()
{
    if (isAIControlled)
    {
        return nullptr;
    }
    return cameraComponent;
}

CollisionType Unit::getCollisionResponse() const
{
    return CollisionType::Overlap;
}

void Unit::moveInDirection(sf::Vector2f dir)
{
    circleShape->move(dir * speed * lastDeltaTime);
}

void Unit::setIsAIControlled(bool isAI)
{
    isAIControlled = isAI;
}

void Unit::onOverlapBegin(std::shared_ptr<Object>& targetObject)
{
    std::shared_ptr<ICollidable> asCollidablePtr = std::dynamic_pointer_cast<ICollidable>(targetObject);

    if (asCollidablePtr)
    {
        if (asCollidablePtr->getCollisionResponse() == CollisionType::Ignore)
        {
            return;
        }
        if (asCollidablePtr->getCollisionResponse() == CollisionType::Overlap)
        {
            tryEatTargetObject(targetObject);
            return;
        }
        if (asCollidablePtr->getCollisionResponse() == CollisionType::Block)
        {
            processBlock(targetObject);
        }
    }
}

void Unit::tryMoveToTargetPos(float deltaTime)
{
    sf::Vector2f distance = targetPos - circleShape->getPosition();

    if (distance.length() < 5.0f)
    {
        hasReachedTargetLocation = true;
        return;
    }
    hasReachedTargetLocation = false;
    
    sf::Vector2f direction = HelperFunctions::normalize(distance);

    circleShape->move(direction * speed * deltaTime);
}

void Unit::tryChooseRandomTargetPos()
{
    if (!hasReachedTargetLocation)
    {
        return;
    }

    float maxCoord = 2000.0f - circleRadius - 10.0f;
    
    targetPos.x = HelperFunctions::getRandomIntInRange(-maxCoord, maxCoord);
    targetPos.y = HelperFunctions::getRandomIntInRange(-maxCoord, maxCoord);

    hasReachedTargetLocation = false;
}

void Unit::tryEatTargetObject(std::shared_ptr<Object>& targetObject)
{
    std::shared_ptr<IEatable> asEatablePtr = std::dynamic_pointer_cast<IEatable>(targetObject);

    if (asEatablePtr)
    {
        sf::Vector2f firstCenter = circleShape->getPosition();
        sf::Vector2f secondCenter = asEatablePtr->getPosition();

        sf::Vector2f delta = secondCenter - firstCenter;

        float targetRadius = asEatablePtr->getRadius();

        if (delta.length() < circleRadius && circleRadius > targetRadius)
        {
            updateCircleRadius(targetRadius + circleRadius);
            asEatablePtr->becomeEaten();
            cameraComponent->setZoomValue(cameraComponent->getRealZoomValue() + targetRadius * 0.002f);

            if (isAIControlled)
            {
                tryChooseRandomTargetPos();
            }
        }
    }
}

void Unit::processBlock(std::shared_ptr<Object>& targetObject)
{
    auto targetShape = targetObject->getShapeBase();

    if (!targetShape)
    {
        return;
    }

    sf::FloatRect rect = targetShape->getGlobalBounds();
    sf::Vector2f circleCenter = circleShape->getPosition();
    
    float closestX = std::clamp(circleCenter.x, rect.position.x, rect.position.x + rect.size.x);
    float closestY = std::clamp(circleCenter.y, rect.position.y, rect.position.y + rect.size.y);

    sf::Vector2f closestPoint = { closestX, closestY };
    sf::Vector2f delta = circleCenter - closestPoint;

    float length = delta.length();

    if (length == 0.f)
    {
        sf::Vector2f rectCenter = rect.getCenter();
        delta = circleCenter - rectCenter;
        length = delta.length();

        if (length == 0.f)
        {
            return;
        }
    }

    sf::Vector2f hitNormal = delta / length;

    circleShape->setPosition(closestPoint + hitNormal * circleRadius);
}
