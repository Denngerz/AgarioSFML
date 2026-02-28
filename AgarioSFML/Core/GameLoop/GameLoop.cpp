#include "GameLoop.h"
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Object/Object.h"
#include "../Time/Time.h"

GameLoop::GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle)
    : currentInputEvent(sf::Event::KeyPressed{})
{
    time = std::make_shared<Time>();
    
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({ windowWidth, windowHeight }),
        windowTitle
    );

    window->setFramerateLimit(60);
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
    while (const std::optional<sf::Event> ev = window->pollEvent())
    {
        currentInputEvent = *ev;
    }
}

void GameLoop::logic()
{
    time->update();
    updateObjects();
}

void GameLoop::draw() const
{
    updateWindow();
}

bool GameLoop::isEndGame() const
{
    return !window->isOpen();
}

void GameLoop::updateWindow() const
{
    window->clear(sf::Color::White);

    for (const auto& shape : shapes)
    {
        if (shape)
            window->draw(*shape);
    }

    window->display();
}

void GameLoop::updateObjects()
{
    for (const auto& obj : tickableObjects)
    {
        if (obj)
        {
            obj->update(time->deltaTime);
        }
    }
}

void GameLoop::addObject(const std::shared_ptr<Object>& obj)
{
    if (!obj)
    {
        return;
    }

    shapes.add(obj->getShapeBase());

    if (obj->getIsTickable())
    {
        tickableObjects.add(obj);
    }

    
}

void GameLoop::removeObject(const std::shared_ptr<Object>& obj)
{
    if (!obj)
    {
        return;
    }

    shapes.remove(obj->getShapeBase());
    tickableObjects.remove(obj);
}

sf::Event& GameLoop::getCurrentInput()
{
    return currentInputEvent;
}

std::weak_ptr<sf::RenderWindow> GameLoop::getWindow() const
{
    return window;
}