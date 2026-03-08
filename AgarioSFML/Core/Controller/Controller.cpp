#include "Controller.h"
#include "../Object/Pawn/Pawn.h"

Controller::Controller(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input): Object(objFactory)
{
    inputManager = input;
}

void Controller::possessPawn(std::shared_ptr<Pawn> targetPawn)
{
    controlledPawn = targetPawn;
    
    auto selfAsObject = Object::shared_from_this();
    
    auto selfAsController = std::static_pointer_cast<Controller>(selfAsObject);

    controlledPawn->becomePossesed(selfAsController);
}

void Controller::unpossessPawn()
{
    if (!controlledPawn)
    {
        return;
    }

    controlledPawn->becomeUnpossesed();
    controlledPawn = nullptr;
}