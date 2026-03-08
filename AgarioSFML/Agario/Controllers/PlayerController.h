#pragma once

#include "../../Core/Controller/Controller.h"

class Game;
class Unit;

class PlayerController: public Controller
{
public:
    PlayerController(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input);

    virtual void possessPawn(std::shared_ptr<Pawn> targetPawn) override;

    virtual void unpossessPawn() override;

    virtual void beginPlay() override;

    void setGamemode(std::shared_ptr<Game> newGamemode);

private:
    std::shared_ptr<Unit> controlledUnit;

    std::weak_ptr<Game> gamemode;
};
