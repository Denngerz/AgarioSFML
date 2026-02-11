#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Renderer/Renderer.h"

class Factory;

class GameLoop: public std::enable_shared_from_this<GameLoop>
{
public:
    virtual ~GameLoop() = default;
    
    GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, sf::Color backgroundColor);

    void runLoop();

    void addUpdatableShape(const std::shared_ptr<sf::Shape>& newShape);

    void removeUpdatableShape(const std::shared_ptr<sf::Shape>& newShape);

protected:
    std::shared_ptr<sf::RenderWindow> window;

    sf::Color windowBGColor;

    std::unique_ptr<Renderer> renderer;

    std::vector<std::shared_ptr<sf::Shape>> updatableShapes;

    std::unique_ptr<Factory> factory;
        
    virtual void generate();
    
    virtual void getInput() const;
    
    virtual void logic();

    void draw() const;

    bool isEndGame() const;
};
