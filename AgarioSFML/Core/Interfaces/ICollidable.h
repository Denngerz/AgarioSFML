#pragma once

enum CollisionType
{
    Ignore = 0,
    Overlap = 1,
    Block = 2
};

class ICollidable
{
public:
    virtual CollisionType getCollisionResponse() const = 0;
};
