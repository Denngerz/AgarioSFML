#include "GameLoop.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Factory/Factory.h"
#include "../Object/Object.h"
#include "../Time/Time.h"

GameLoop::GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, sf::Color backgroundColor)
{
    Time::init();

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode({windowWidth, windowHeight}), windowTitle);
    
    window->setFramerateLimit(60);

    windowBGColor = backgroundColor;

    renderer = std::make_unique<Renderer>();

    factory = std::make_unique<Factory>();
}

void GameLoop::runLoop()
{
    generate();
    
    while (!isEndGame())
    {
        getInput();
        logic();
        draw();
    }
}

void GameLoop::generate()
{
    
}

void GameLoop::getInput()
{
}

void GameLoop::logic()
{
    Time::update();
    updateObjects();
}

void GameLoop::draw() const
{
    renderer->updateWindow(*window, windowBGColor, updatableShapes);
}

bool GameLoop::isEndGame() const
{
    return !window->isOpen();
}

void GameLoop::updateObjects()
{
    for (auto obj : updatableObjects)
    {
        obj->update(Time::deltaTime);
    }
}

void GameLoop::addUpdatableShape(const std::shared_ptr<sf::Shape>& newShape)
{
    updatableShapes.emplace_back(newShape);
}

void GameLoop::removeUpdatableShape(const std::shared_ptr<sf::Shape>& oldShape)
{
    if (oldShape)
    {
        auto it = std::find(updatableShapes.begin(), updatableShapes.end(), oldShape);
        updatableShapes.erase(it);
    }
}

void GameLoop::addUpdatableObject(const std::shared_ptr<Object>& newObject)
{
    if (newObject)
    {
        updatableObjects.emplace_back(newObject);
    }
}

void GameLoop::removeUpdatableObject(const std::shared_ptr<Object>& oldObject)
{
    if (oldObject)
    {
        auto it = std::find(updatableObjects.begin(), updatableObjects.end(), oldObject);
        updatableObjects.erase(it);
    }
}

std::weak_ptr<sf::RenderWindow> GameLoop::getWindow() const
{
    return window;
}
