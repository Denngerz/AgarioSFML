#include "Object.h"
#include "../GameLoop/GameLoop.h"

Object::Object(std::shared_ptr<GameLoop> gameLoop): currentGameLoop(std::move(gameLoop)), isTickable(true)
{
}

void Object::beginPlay()
{
}

const std::shared_ptr<sf::Shape>& Object::getShapeBase() const
{
    static const std::shared_ptr<sf::Shape> Empty{};
    return Empty;
}

void Object::update(float deltaTime)
{
}

bool Object::getIsTickable() const
{
    return isTickable;
}

void Object::destroySelf()
{
    if (auto gl = currentGameLoop.lock())
    {
        gl->removeObject(shared_from_this());
    }
}
