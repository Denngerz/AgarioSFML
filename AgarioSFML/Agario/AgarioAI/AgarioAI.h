#pragma once
#include "../../Object/CircleObject/CircleObject.h"

class AgarioAI: public CircleObject
{
public:
    AgarioAI(std::shared_ptr<GameLoop>& gameLoop, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0), sf::Vector2f position = sf::Vector2f(0,0));

    void update(float deltaTime) override;

    void initializeObject() override;
    
private:
    float speed;

    sf::Vector2f targetPos;

    void moveToTargetPos(float deltaTime);

    sf::Vector2f normalize(sf::Vector2f v);
    
    bool hasReachedTargetPos();

    void chooseRandomTargetPos();
    
    int getRandomIntInRange(int min, int max);
};
