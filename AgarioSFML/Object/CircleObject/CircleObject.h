#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Object.h"

class CircleObject: public Object
{
public:
    CircleObject(std::shared_ptr<GameLoop>& gameLoop, float radius = 10.0f, sf::Color circleColor = sf::Color(225,0,0,225), sf::Vector2f position = sf::Vector2f(0,0));

    void initializeObject() override;

    std::shared_ptr<sf::Shape> circleShape;
};
