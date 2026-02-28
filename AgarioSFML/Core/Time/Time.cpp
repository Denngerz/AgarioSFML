#include "Time.h"
#include <SFML/System.hpp>

Time::Time(): deltaTime(0)
{
    clock = new sf::Clock();
}

Time::~Time()
{
    destroy();
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