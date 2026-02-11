#include "Renderer.h"
#include <SFML/Graphics.hpp>

void Renderer::updateWindow(sf::RenderWindow& window, sf::Color windowBG, const std::vector<std::shared_ptr<sf::Shape>>& shapesToDraw)
{
    window.clear(windowBG);

    for (const auto& shape : shapesToDraw)
    {
        if (shape)
        {
            window.draw(*shape);
        }
    }
    
    window.display();
}