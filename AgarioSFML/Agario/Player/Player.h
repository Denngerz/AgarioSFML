#pragma once
#include "../../Core/Object/CircleObject/CircleObject.h"

namespace sf
{
    class RenderWindow;
}

class Player: public CircleObject
{
public:
    Player(std::shared_ptr<GameLoop>& gameLoop, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0), bool isAI = false);

    void update(float deltaTime) override;
    
private:
    float speed;

    sf::Vector2f targetPos;

    bool isAIControlled;

    bool hasReachedTargetLocation;
    
    uint8_t getRandomUInt8_t() const;

    void proccessCurrentInputEvent();

    void tryMoveToTargetPos(float deltaTime);

    sf::Vector2f normalize(sf::Vector2f v) const;

    void tryChooseRandomTargetPos();
    
    int getRandomIntInRange(int min, int max) const;
};
