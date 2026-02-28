#pragma once
#include "../Core/GameLoop/GameLoop.h"
#include "../Core/Object/Object.h"

class Player;

namespace sf
{
    class CircleShape;
}

class Game: public Object
{
public:
    Game(std::shared_ptr<GameLoop> gameLoop);

    const std::shared_ptr<sf::Shape>& getShapeBase() const override;

    void beginPlay() override;

private:
    void generatePlayer();

    void generateEnemies();

    std::shared_ptr<Player> player;

    std::vector<std::shared_ptr<Player>> enemies;
};
