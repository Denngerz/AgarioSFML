#pragma once
#include <memory>
#include "../GameLoop/GameLoop.h"

class Object;
class Controller; 

class ObjectFactory : public std::enable_shared_from_this<ObjectFactory>
{
public:
    explicit ObjectFactory(const std::shared_ptr<GameLoop>& inGameLoop): gameLoop(inGameLoop) {}

    template<class T, class... Args>
    std::shared_ptr<T> createObject(Args&&... args)
    {
        static_assert(std::is_base_of_v<Object, T>, "T must be an object");

        auto lockedGameLoop = gameLoop.lock();
        if (!lockedGameLoop) return nullptr;

        std::shared_ptr<T> object;

        if constexpr (std::is_base_of_v<Controller, T>)
        {
            object = std::make_shared<T>(shared_from_this(), lockedGameLoop->getInputManager(), std::forward<Args>(args)...);
        }
        else
        {
            object = std::make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
        }
        
        object->beginPlay();
        lockedGameLoop->addObject(std::static_pointer_cast<Object>(object));
        return object;
    }

private:
    std::weak_ptr<GameLoop> gameLoop;
};