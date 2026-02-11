#include "Factory.h"
#include "../Object/Object.h"
#include "../Core/GameLoop.h"

void Factory::registerObjectShape(std::shared_ptr<GameLoop>& game_loop, std::shared_ptr<Object> obj)
{
    game_loop->addUpdatableShape(obj->getShapeBase());
}
