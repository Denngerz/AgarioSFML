#pragma once
#include "../Core/GameLoop/GameLoop.h"
#include "../Core/Object/Object.h"

class Unit;

namespace sf
{
    class CircleShape;
}

class Game: public Object
{
public:
    Game(std::shared_ptr<ObjectFactory> objectFactory);

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    void beginPlay() override;

    virtual void update(float deltaTime) override;

protected:
    void onOverlapBegin(std::shared_ptr<Object>& targetObject) override;

private:
    std::shared_ptr<Unit> player;

    std::vector<std::shared_ptr<Unit>> enemies;

    float spawnTimer;

    float foodSpawnInterval;
    
    void generatePlayer();

    void generateEnemies();

    void spawnFood();

    sf::Vector2f getRandomLocation();

    sf::Color getRandomColor();
};
