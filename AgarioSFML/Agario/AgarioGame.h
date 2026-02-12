#pragma once
#include "../GameLoop/GameLoop.h"

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

    std::shared_ptr<AgarioPlayer> player;

    sf::Event currentInputEvent; 
};
