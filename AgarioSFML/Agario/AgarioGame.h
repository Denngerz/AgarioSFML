#pragma once
#include "../GameLoop/GameLoop.h"

class AgarioAI;
class AgarioPlayer;

namespace sf
{
    class CircleShape;
}

class AgarioGame: public GameLoop
{
public:
    AgarioGame();

protected:
    void generate() override;

    void getInput() override;

    void logic() override;

private:
    void generatePlayer();

    void generateEnemies();

    std::shared_ptr<AgarioPlayer> player;

    std::vector<std::shared_ptr<AgarioAI>> enemies;

    sf::Event currentInputEvent; 
};
