#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Object/Object.h"

class World : public Object
{
public:
    World(std::shared_ptr<ObjectFactory> objFactory);

    void update(float deltaTime) override;
    
    sf::Vector2f worldToSFML(sf::Vector2f worldPos) const;
    
    sf::Vector2f sfmlToWorld(sf::Vector2f sfmlPos) const;
    
    sf::Vector2f pixelToWorld(sf::Vector2i screenPixel, const sf::RenderWindow& window) const;
    
    sf::Vector2i worldToPixel(sf::Vector2f worldPos, const sf::RenderWindow& window) const;

    void registerObject(const std::shared_ptr<Object>& obj);

private:
    std::vector<std::weak_ptr<Object>> spawnedObjects;

    void cleanupDestroyedObjects();
};