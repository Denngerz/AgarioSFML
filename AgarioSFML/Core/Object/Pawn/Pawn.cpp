#include "Pawn.h"

#include "../../Controller/Controller.h"

Pawn::Pawn(std::shared_ptr<ObjectFactory> objFactory): Object(objFactory)
{
}

std::shared_ptr<Controller> Pawn::getCurrentController()
{
    return currentController;
}

void Pawn::becomePossesed(std::shared_ptr<Controller> newController)
{
    if (newController)
    {
        currentController = newController;
    }
}

void Pawn::becomeUnpossesed()
{
    currentController = nullptr;
}
