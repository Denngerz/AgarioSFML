#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf
{
    class Shape;
}

class Renderer
{
public:
    void updateWindow(sf::RenderWindow& window, sf::Color windowBG, const std::vector<std::shared_ptr<sf::Shape>>& shapesToDraw);
};
