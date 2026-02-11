#pragma once
#include "Core/GameLoop.h"

namespace sf
{
    class CircleShape;
}

class AgarioGame: public GameLoop
{
public:
    AgarioGame();

    void generate() override;

private:
    void generatePlayers();
};
