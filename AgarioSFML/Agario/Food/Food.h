#pragma once
#include "../../Core/Object/Object.h"
#include "../Interfaces/IEatable.h"

class Food: public Object, public IEatable
{
public:
    Food(std::shared_ptr<ObjectFactory> objFactory, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0));

    virtual void becomeEaten() override;

    virtual float getRadius() override;

    virtual sf::Vector2f getPosition() override;
    
    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

protected:
    std::shared_ptr<sf::Shape> circleShape;

    float circleRadius;
};
