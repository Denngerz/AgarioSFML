#include "GameLoop.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Factory/Factory.h"
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

void GameLoop::getInput() const
{
    
}

void GameLoop::logic()
{
    Time::update();
}

void GameLoop::draw() const
{
    renderer->updateWindow(*window, windowBGColor, updatableShapes);
}

bool GameLoop::isEndGame() const
{
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            return true;
        }
    }
    
    return false;
}

void GameLoop::addUpdatableShape(const std::shared_ptr<sf::Shape>& newShape)
{
    updatableShapes.emplace_back(newShape);
}

void GameLoop::removeUpdatableShape(const std::shared_ptr<sf::Shape>& oldShape)
{
    auto it = std::find(updatableShapes.begin(), updatableShapes.end(), oldShape);
    updatableShapes.erase(it);
}