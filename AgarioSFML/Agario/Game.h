#pragma once
#include "../Core/Object/Object.h"

class Wall;
class PlayerController;
class Unit;
class FoodManager;

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

    std::shared_ptr<Unit> getRandomUnit(std::shared_ptr<Unit> exeptionUnit = nullptr) const;

private:
    std::shared_ptr<Unit> player;

    std::shared_ptr<PlayerController> playerController;

    std::vector<std::shared_ptr<Unit>> units;

    std::vector<std::shared_ptr<Wall>> walls;

    std::shared_ptr<FoodManager> foodManager;

    sf::Vector2f mapSize;

    void generateWalls();

    void generatePlayer();

    void generateUnits();

    void generateFoodManager();
};
