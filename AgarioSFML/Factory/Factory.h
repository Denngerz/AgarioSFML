#pragma once
#include <memory>

class Object;
class GameLoop;

class Factory
{
public:
    template<class T, class... Args>
    static std::shared_ptr<T> createObject(std::shared_ptr<GameLoop> gameLoop, Args&&... args)
    {
        static_assert(std::is_base_of_v<Object, T>, "T must be an object");
        
        std::shared_ptr<T> obj = std::make_shared<T>(gameLoop, std::forward<Args>(args)...);
        
        obj->initializeObject();

        registerObjectShape(gameLoop, obj);

        return obj;
    }

    static void registerObjectShape(std::shared_ptr<GameLoop>& game_loop, std::shared_ptr<Object> obj);
};
