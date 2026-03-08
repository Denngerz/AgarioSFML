#pragma once
#include "../../Core/Object/CircleObject/CircleObject.h"
#include "../Interfaces/IEatable.h"

class Controller;

namespace sf
{
    class RenderWindow;
}

class Unit: public CircleObject, public IEatable
{
public:
    Unit(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0), bool isAI = false);

    void update(float deltaTime) override;

    virtual void becomeEaten() override;
    
    void moveInDirection(sf::Vector2f dir);

    void setIsAIControlled(bool isAI);

    virtual void becomeUnpossesed() override;

protected:
    virtual void onOverlapBegin(std::shared_ptr<Object>& targetObject) override;

private:
    float speed;

    sf::Vector2f targetPos;

    float lastDeltaTime;

    bool isAIControlled;

    bool hasReachedTargetLocation;

    void tryMoveToTargetPos(float deltaTime);

    void tryChooseRandomTargetPos();

    void tryEatTargetObject(std::shared_ptr<Object>& targetObject);
};
