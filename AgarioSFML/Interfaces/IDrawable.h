#pragma once
#include <memory>

namespace sf
{
    class Shape;
}

class IDrawable
{
public:
    virtual const std::shared_ptr<sf::Shape>& getShapeBase() const = 0;
};
