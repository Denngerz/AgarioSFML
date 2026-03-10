#pragma once
#include "../../Core/Object/Pawn/Pawn.h"

class CirclePawn: public Pawn
{
public:
    CirclePawn(std::shared_ptr<ObjectFactory> objFactory, float radius, sf::Color circleColor, sf::Vector2f position);

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    void update(float deltaTime) override ;

    float getCircleRadius();

    virtual void beginPlay() override;

protected:
    std::shared_ptr<sf::Shape> circleShape;

    float circleRadius;

    void updateCircleRadius(float newRadius);
};
