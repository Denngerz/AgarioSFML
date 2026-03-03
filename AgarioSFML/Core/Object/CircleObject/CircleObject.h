#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Object.h"

class CircleObject: public Object
{
public:
    CircleObject(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor, sf::Vector2f position);

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    void update(float deltaTime) override ;

    float getCircleRadius();

protected:
    std::shared_ptr<sf::Shape> circleShape;

    float circleRadius;

    void updateCircleRadius(float newRadius);
};