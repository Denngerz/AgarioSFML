#pragma once
#include <inttypes.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class HelperFunctions
{
public:
    static sf::Vector2f normalize(sf::Vector2f v);

    static int getRandomIntInRange(int min, int max);

    static uint8_t getRandomUInt8_t();

    static sf::Color getRandomColor();
};
