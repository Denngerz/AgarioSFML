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
    tryEatTargetObject(targetObject);
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

    sf::Vector2u mapSize = sf::Vector2u(1400, 1200);

    targetPos.x = HelperFunctions::getRandomIntInRange(0, mapSize.x);
    targetPos.y = HelperFunctions::getRandomIntInRange(0, mapSize.y);

    hasReachedTargetLocation = false;
}

void Unit::tryEatTargetObject(std::shared_ptr<Object>& targetObject)
{
    std::shared_ptr<IEatable> interfacePtr = std::dynamic_pointer_cast<IEatable>(targetObject);

    if (interfacePtr)
    {
        sf::Vector2f firstCenter = circleShape->getPosition();
        sf::Vector2f secondCenter = interfacePtr->getPosition();

        sf::Vector2f delta = secondCenter - firstCenter;

        float targetRadius = interfacePtr->getRadius();

        if (delta.length() < circleRadius && circleRadius > targetRadius)
        {
            updateCircleRadius(targetRadius + circleRadius);
            interfacePtr->becomeEaten();
            cameraComponent->setZoomValue(cameraComponent->getRealZoomValue() + targetRadius * 0.001f);  
        }
    }
}
