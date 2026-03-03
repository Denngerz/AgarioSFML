#include "HelperFunctions.h"
#include <cmath>
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
