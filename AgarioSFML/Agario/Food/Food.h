#pragma once
#include "../../Core/Object/CircleObject/CircleObject.h"
#include "../Interfaces/IEatable.h"

class Food: public CircleObject, public IEatable
{
public:
    Food(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0));

    virtual void becomeEaten() override;
};
