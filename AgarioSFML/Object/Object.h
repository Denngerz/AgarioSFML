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

    virtual void initializeObject();

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    virtual void update(float deltaTime) override;

    void destroySelf();

protected:
    std::weak_ptr<GameLoop> currentGameLoop;
};
