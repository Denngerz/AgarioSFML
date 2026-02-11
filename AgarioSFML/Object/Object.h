#pragma once
#include <memory>

class GameLoop;

namespace sf
{
    class Color;
    class CircleShape;
    class Shape;
}

class Object
{
public:
    virtual ~Object() = default;
    explicit Object(std::shared_ptr<GameLoop> gameLoop): currentGameLoop(std::move(gameLoop)) {}

    virtual void initializeObject();

    const std::shared_ptr<sf::Shape>& getShapeBase() const;

    void destroySelf();

protected:
    void setShapeBase(std::shared_ptr<sf::Shape>& newShape);
    
    std::weak_ptr<GameLoop> currentGameLoop;

    std::shared_ptr<sf::Shape> shapeBase;
};
