#pragma once
#include <SFML/Window/Event.hpp>

class IUpdatable
{
public:
    virtual void update(float deltaTime) = 0;
};
