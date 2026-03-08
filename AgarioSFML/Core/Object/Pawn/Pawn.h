#pragma once

#include "../Object.h"

class Controller;

class Pawn: public Object
{
public:
    Pawn(std::shared_ptr<ObjectFactory> objFactory);

    std::shared_ptr<Controller> getCurrentController();

    virtual void becomePossesed(std::shared_ptr<Controller> newController);
    
    virtual void becomeUnpossesed();

private:
    std::shared_ptr<Controller> currentController;
};
