#pragma once
#include "../../Object/CircleObject/CircleObject.h"

namespace sf
{
    class RenderWindow;
}

class AgarioPlayer: public CircleObject
{
public:
    AgarioPlayer(std::shared_ptr<GameLoop>& gameLoop, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0));

    void update(float deltaTime) override;

    void receiveInput(const sf::Event& event);
    
private:
    float speed;

    sf::Vector2f targetPos;
    
    uint8_t getRandomUInt8_t();

    void proccessInputEvent(sf::Event event);

    void moveToTargetPos(float deltaTime);

    sf::Vector2f normalize(sf::Vector2f v);
};
