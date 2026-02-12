#include "Object.h"
#include "../GameLoop/GameLoop.h"

Object::Object(std::shared_ptr<GameLoop> gameLoop): currentGameLoop(std::move(gameLoop))
{
}

void Object::initializeObject()
{
}

const std::shared_ptr<sf::Shape>& Object::getShapeBase() const
{
    return nullptr;
}

void Object::update(float deltaTime)
{
}

void Object::destroySelf()
{
    if (auto gl = currentGameLoop.lock())
    {
        gl->removeUpdatableShape(getShapeBase());
        gl->removeUpdatableObject(shared_from_this());
    }
}
