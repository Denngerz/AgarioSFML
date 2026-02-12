#include "AgarioPlayer.h"
#include "../../GameLoop/GameLoop.h"
#include <random>

AgarioPlayer::AgarioPlayer(std::shared_ptr<GameLoop>& gameLoop, float radius, sf::Color circleColor, sf::Vector2f position)
    : CircleObject(gameLoop, radius, circleColor, position),
      speed(100)
{
    circleShape->setFillColor(sf::Color(getRandomUInt8_t(), getRandomUInt8_t(), getRandomUInt8_t()));
}

void AgarioPlayer::update(float deltaTime)
{
    moveToTargetPos(deltaTime);
}

void AgarioPlayer::receiveInput(const sf::Event& event)
{
    proccessInputEvent(event);
}

uint8_t AgarioPlayer::getRandomUInt8_t()
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(0, 255)(rng);
    return static_cast<uint8_t>(value);
}

void AgarioPlayer::proccessInputEvent(sf::Event event)
{
    if (const auto* mv = event.getIf<sf::Event::MouseMoved>())
    {
        sf::Vector2i pixel = sf::Vector2i(mv->position.x, mv->position.y);
        
        std::weak_ptr<sf::RenderWindow> window = currentGameLoop.lock()->getWindow();
        targetPos = window.lock()->mapPixelToCoords(pixel);
    }
}


void AgarioPlayer::moveToTargetPos(float deltaTime)
{
    sf::Vector2f distance = targetPos - circleShape->getPosition();

    if (distance.length() < 1.0f)
    {
        return;
    }
    
    sf::Vector2f direction = normalize(distance);

    circleShape->move(direction * speed * deltaTime);
}

sf::Vector2f AgarioPlayer::normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    
    if (len > 0.00001f)
    {
        return sf::Vector2f(v.x / len, v.y / len);
    }
    
    return sf::Vector2f(0.f, 0.f);
}