#pragma once
#include "CirclePawn.h"
#include "../../Core/Interfaces/ICameraProvider.h"
#include "../../Core/Interfaces/ICollidable.h"
#include "../Interfaces/IEatable.h"

class Controller;

namespace sf
{
    class RenderWindow;
}

class Unit: public CirclePawn, public IEatable, public ICameraProvider, public ICollidable
{
public:
    Unit(std::shared_ptr<ObjectFactory> objFactory, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0), bool isAI = false);

    void update(float deltaTime) override;

    virtual void becomeEaten() override;

    virtual float getArea() override;

    virtual sf::Vector2f getPosition() override;

    virtual std::shared_ptr<CameraComponent> getCameraComponent() override;

    virtual CollisionType getCollisionResponse() const override;

    virtual void becomePossesed(std::shared_ptr<Controller> newController) override;

    virtual void becomeUnpossesed() override;

    virtual bool getIsMainProvider() const override;
    
    void moveInDirection(sf::Vector2f dir);

    void setIsAIControlled(bool isAI);

    void sprint();

    void stopSprint();

protected:
    virtual void onOverlapBegin(std::shared_ptr<Object>& targetObject) override;

private:
    float speed;

    float speedBoost;

    sf::Vector2f targetPos;

    float lastDeltaTime;

    bool isAIControlled;

    bool isSprinting;

    bool hasReachedTargetLocation;

    std::shared_ptr<CameraComponent> cameraComponent;

    CollisionType collisionType;

    void tryMoveToTargetPos(float deltaTime);

    void tryChooseRandomTargetPos();

    void tryEatTargetObject(std::shared_ptr<Object>& targetObject);

    void processBlock(std::shared_ptr<Object>& targetObject);
};
