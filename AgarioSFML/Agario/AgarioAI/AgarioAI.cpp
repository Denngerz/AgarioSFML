#include "AgarioAI.h"
#include <random>
#include <SFML/Graphics.hpp>
#include "../../GameLoop/GameLoop.h"

AgarioAI::AgarioAI(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor, sf::Vector2f position)
    :CircleObject(gameLoop, radius, circleColor, position),
     speed(100)
{
}

void AgarioAI::update(float deltaTime)
{
    CircleObject::update(deltaTime);

    if (hasReachedTargetPos())
    {
        chooseRandomTargetPos();
    }
    else
    {
        moveToTargetPos(deltaTime);
    }
    
}

void AgarioAI::initializeObject()
{
    CircleObject::initializeObject();

    chooseRandomTargetPos();
}

void AgarioAI::moveToTargetPos(float deltaTime)
{
    sf::Vector2f distance = targetPos - circleShape->getPosition();
    
    sf::Vector2f direction = normalize(distance);

    circleShape->move(direction * speed * deltaTime);
}

bool AgarioAI::hasReachedTargetPos()
{
    sf::Vector2f distance = targetPos - circleShape->getPosition();

    return distance.length() < 1.0f;
}

void AgarioAI::chooseRandomTargetPos()
{
    std::weak_ptr<sf::RenderWindow> window = currentGameLoop.lock()->getWindow();
    sf::Vector2u mapSize = window.lock()->getSize();

    targetPos.x = getRandomIntInRange(0, mapSize.x);
    targetPos.y = getRandomIntInRange(0, mapSize.y);
}

int AgarioAI::getRandomIntInRange(int min, int max)
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(min, max)(rng);
    return value;
}

sf::Vector2f AgarioAI::normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    
    if (len > 0.00001f)
    {
        return sf::Vector2f(v.x / len, v.y / len);
    }
    
    return sf::Vector2f(0.f, 0.f);
}