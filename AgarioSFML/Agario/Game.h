#pragma once
#include "../Core/GameLoop/GameLoop.h"
#include "../Core/Object/Object.h"

class Wall;
class PlayerController;
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

private:
    std::shared_ptr<Unit> player;

    std::shared_ptr<PlayerController> playerController;

    std::vector<std::shared_ptr<Unit>> enemies;

    std::vector<std::shared_ptr<Wall>> walls;

    sf::Vector2f mapSize;

    float spawnTimer;

    float foodSpawnInterval;

    void generateLevel();
    
    void generatePlayer();

    void generateEnemies();

    void spawnFood();

    sf::Vector2f getRandomLocation();

    sf::Color getRandomColor();
};
