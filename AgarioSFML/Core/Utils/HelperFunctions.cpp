#include "HelperFunctions.h"
#include <cmath>
#include <random>
#include <SFML/System/Vector2.hpp>

sf::Vector2f HelperFunctions::normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    
    if (len > 0.00001f)
    {
        return sf::Vector2f(v.x / len, v.y / len);
    }
    
    return sf::Vector2f(0.f, 0.f);
}

int HelperFunctions::getRandomIntInRange(int min, int max)
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(min, max)(rng);
    return value;
}

uint8_t HelperFunctions::getRandomUInt8_t()
{
    static std::mt19937 rng{std::random_device{}()};
    int value = std::uniform_int_distribution<int>(0, 255)(rng);
    return static_cast<uint8_t>(value);
}