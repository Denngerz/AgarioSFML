#pragma once

class IEatable
{
public:
    virtual void becomeEaten() = 0;

    virtual float getRadius() = 0;

    virtual sf::Vector2f getPosition() = 0;
};
