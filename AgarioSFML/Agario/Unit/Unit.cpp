#include "Unit.h"
#include "../../Core/GameLoop/GameLoop.h"
#include <SFML/Window/Event.hpp> 
#include <random>

Unit::Unit(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor,sf::Vector2f position, bool isAI)
    : CircleObject(gameLoop, radius, circleColor, position),
      speed(200),
      hasReachedTargetLocation(true)
{
    isAIControlled = isAI;
}

void Unit::update(float deltaTime)
{
    CircleObject::update(deltaTime);

    if (isAIControlled)
    {
        tryChooseRandomTargetPos();
    }
    else
    {
        proccessCurrentInputEvent();
    }

    tryMoveToTargetPos(deltaTime);
}

void Unit::becomeEaten()
{
    destroySelf();
}

void Unit::onOverlapBegin(std::shared_ptr<Object>& targetObject)
{
    tryEatTargetObject(targetObject);
}

void Unit::proccessCurrentInputEvent()
{
    auto event = currentGameLoop.lock()->getCurrentInput();
    
    if (const auto* mv = event.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2i pixel = sf::Vector2i(mv->position.x, mv->position.y);
        
        std::weak_ptr<sf::RenderWindow> window = currentGameLoop.lock()->getWindow();
        targetPos = window.lock()->mapPixelToCoords(pixel);
    }
}

uint8_t Unit::getRandomUInt8_t() const
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(0, 255)(rng);
    return static_cast<uint8_t>(value);
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
    
    sf::Vector2f direction = normalize(distance);

    circleShape->move(direction * speed * deltaTime);
}

sf::Vector2f Unit::normalize(sf::Vector2f v) const
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    
    if (len > 0.00001f)
    {
        return sf::Vector2f(v.x / len, v.y / len);
    }
    
    return sf::Vector2f(0.f, 0.f);
}

void Unit::tryChooseRandomTargetPos()
{
    if (!hasReachedTargetLocation)
    {
        return;
    }
    
    std::weak_ptr<sf::RenderWindow> window = currentGameLoop.lock()->getWindow();
    sf::Vector2u mapSize = window.lock()->getSize();

    targetPos.x = getRandomIntInRange(0, mapSize.x);
    targetPos.y = getRandomIntInRange(0, mapSize.y);

    hasReachedTargetLocation = false;
}

int Unit::getRandomIntInRange(int min, int max) const
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(min, max)(rng);
    return value;
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
