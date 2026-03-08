#include "Unit.h"
#include <random>
#include "../../Core/GameLoop/GameLoop.h"
#include "../../Core/Utils/HelperFunctions.h"
#include "../../Core/Controller/Controller.h"

Unit::Unit(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input, float radius, sf::Color circleColor,sf::Vector2f position, bool isAI)
    : CircleObject(objFactory, input, radius, circleColor, position),
      speed(200),
      lastDeltaTime(0),
      hasReachedTargetLocation(true)
{
    isAIControlled = isAI;
}

void Unit::update(float deltaTime)
{
    CircleObject::update(deltaTime);

    lastDeltaTime = deltaTime;
    
    if (isAIControlled)
    {
        tryChooseRandomTargetPos();
        tryMoveToTargetPos(deltaTime);
    }
}

void Unit::becomeEaten()
{
    if (currentController)
    {
        currentController->unpossessObject();
    }
    
    destroySelf();
}

void Unit::moveInDirection(sf::Vector2f dir)
{
    circleShape->move(dir * speed * lastDeltaTime);
}

void Unit::setIsAIControlled(bool isAI)
{
    isAIControlled = isAI;
}

void Unit::becomeUnpossesed()
{
    CircleObject::becomeUnpossesed();
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
        auto targetAsCircleObject = std::dynamic_pointer_cast<CircleObject>(targetObject);
        
        if (targetAsCircleObject)
        {
            sf::Vector2f firstCenter = circleShape->getPosition();
            sf::Vector2f secondCenter = targetAsCircleObject->getShapeBase()->getPosition();

            sf::Vector2f delta = secondCenter - firstCenter;

            float targetRadius = targetAsCircleObject->getCircleRadius();

            if (delta.length() < circleRadius && circleRadius > targetRadius)
            {
                updateCircleRadius(targetRadius + circleRadius);
                interfacePtr->becomeEaten();
            }
        }
    }
}
