#pragma once

class IUpdatable
{
public:
    virtual void update(float deltaTime) = 0;
};
