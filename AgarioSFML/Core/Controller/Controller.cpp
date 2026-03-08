#include "Controller.h"

Controller::Controller(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input): Object(objFactory, input)
{
}

void Controller::possessObject(std::shared_ptr<Object> targetObj)
{
    controlledObject = targetObj;
    
    auto selfAsObject = Object::shared_from_this();
    
    auto selfAsController = std::static_pointer_cast<Controller>(selfAsObject);

    controlledObject->becomePossesed(selfAsController);
}

void Controller::unpossessObject()
{
    if (!controlledObject)
    {
        return;
    }

    controlledObject->becomeUnpossesed();
    controlledObject = nullptr;
}

void Controller::beginPlay()
{
    Object::beginPlay();
}

