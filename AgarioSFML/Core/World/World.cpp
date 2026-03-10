#include "World.h"


World::World(std::shared_ptr<ObjectFactory> objFactory)
    : Object(objFactory)
{
}

void World::update(float deltaTime)
{
    cleanupDestroyedObjects();
}

sf::Vector2f World::worldToSFML(sf::Vector2f worldPos) const
{
    return { worldPos.x, -worldPos.y };
}

sf::Vector2f World::sfmlToWorld(sf::Vector2f sfmlPos) const
{
    return { sfmlPos.x, -sfmlPos.y };
}

sf::Vector2f World::pixelToWorld(sf::Vector2i screenPixel, const sf::RenderWindow& window) const
{
    return sfmlToWorld(window.mapPixelToCoords(screenPixel));
}

sf::Vector2i World::worldToPixel(sf::Vector2f worldPos, const sf::RenderWindow& window) const
{
    return window.mapCoordsToPixel(worldToSFML(worldPos));
}

void World::registerObject(const std::shared_ptr<Object>& obj)
{
    if (obj)
    {
        spawnedObjects.emplace_back(obj);
        obj->setCurrentWorld(std::static_pointer_cast<World>(shared_from_this()));
    }
}

void World::cleanupDestroyedObjects()
{
    size_t currentIndex = 0;

    while (currentIndex < spawnedObjects.size())
    {
        auto obj = spawnedObjects[currentIndex].lock();
        if (!obj || !obj->getIsActive())
        {
            spawnedObjects[currentIndex] = spawnedObjects.back();
            spawnedObjects.pop_back();
        }
        else
        {
            ++currentIndex;
        }
    }
}