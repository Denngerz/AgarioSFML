#pragma once
#include <memory>

#include "../Interfaces/IDrawable.h"
#include "../Interfaces/IUpdatable.h"

class GameLoop;

namespace sf
{
    class Color;
    class CircleShape;
    class Shape;
}

class Object: public IDrawable, IUpdatable, public std::enable_shared_from_this<Object>
{
public:
    virtual ~Object() = default;
    explicit Object(std::shared_ptr<GameLoop> gameLoop);

    virtual void beginPlay();

    void destroySelf();

    virtual void update(float deltaTime) override;

    bool getIsTickable() const;

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    bool getIsActive() const;

    virtual void checkCollisionWithObject(std::shared_ptr<Object>& targetObject);

protected:
    std::weak_ptr<GameLoop> currentGameLoop;

    bool isActive;

    bool isTickable;

    virtual void onOverlapBegin(std::shared_ptr<Object>& targetCircleObject) = 0;
};
