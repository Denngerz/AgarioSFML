#pragma once

class IEatable
{
public:
    virtual void becomeEaten() = 0;

    virtual float getArea() = 0;

    virtual sf::Vector2f getPosition() = 0;
};
