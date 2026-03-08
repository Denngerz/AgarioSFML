#pragma once
#include <memory>

#include "../Factories/ObjectFactory.h"
#include "../Interfaces/IDrawable.h"
#include "../Interfaces/IUpdatable.h"

class Controller;

namespace sf
{
    class Color;
    class CircleShape;
    class Shape;
}

class Object: public IDrawable, public IUpdatable, public std::enable_shared_from_this<Object>
{
public:
    virtual ~Object() = default;
    explicit Object(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input);

    virtual void beginPlay();

    void destroySelf();

    virtual void update(float deltaTime) override;

    bool getIsTickable() const;

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    bool getIsActive() const;

    virtual void checkCollisionWithObject(std::shared_ptr<Object>& targetObject);

    virtual void becomePossesed(std::shared_ptr<Controller> newController);
    
    virtual void becomeUnpossesed();

protected:
    bool isActive;

    bool isTickable;

    std::shared_ptr<InputManager> inputManager;

    std::shared_ptr<Controller> currentController;

    virtual void onOverlapBegin(std::shared_ptr<Object>& targetCircleObject);

    template<class T, class... Args>
    std::shared_ptr<T> spawnObjectOfClass(Args&&... args)
    {
        static_assert(std::is_base_of_v<Object, T>, "T must derive from Object");

        if (!objectFactory)
        {
            return nullptr;
        }

        return objectFactory->template createObject<T>(std::forward<Args>(args)...);
    }

private:
    std::shared_ptr<ObjectFactory> objectFactory;
};
