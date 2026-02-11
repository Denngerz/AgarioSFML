#include "Time.h"
#include <SFML/System.hpp>

sf::Clock* Time::clock = nullptr;
float Time::deltaTime = 0.0f;

void Time::init()
{
    clock = new sf::Clock();
}

void Time::destroy()
{
    delete clock; 
    clock = nullptr;
}

void Time::update()
{
    if (clock)
    {
        deltaTime = clock->restart().asSeconds();
    }
}

float Time::getDeltaTime()
{
    return deltaTime;
}