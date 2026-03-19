#pragma once
#include "../Object.h"

namespace sf
{
    class Drawable;
}

class Widget: public Object
{
public:
    explicit Widget(std::shared_ptr<ObjectFactory> objFactory);

    virtual const std::shared_ptr<sf::Drawable>& getDrawable() const = 0;

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;
};