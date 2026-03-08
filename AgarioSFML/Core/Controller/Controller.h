#pragma once

#include "../../Core/Object/Object.h"

class Unit;

class Controller: public Object
{
public:
    Controller(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input);

    virtual void possessObject(std::shared_ptr<Object> targetObj);

    virtual void unpossessObject();

    virtual void beginPlay() override;
     
protected:
    std::shared_ptr<Object> controlledObject;
};
