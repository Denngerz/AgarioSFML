#pragma once

#include "../../Core/Object/Object.h"

class Pawn;

class Controller: public Object
{
public:
    Controller(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input);

    virtual void possessPawn(std::shared_ptr<Pawn> targetObj);

    virtual void unpossessPawn();
     
protected:
    std::shared_ptr<Pawn> controlledPawn;

    std::shared_ptr<InputManager> inputManager;
};
