#include "Factory.h"
#include "../Object/Object.h"
#include "../GameLoop/GameLoop.h"

void Factory::registerObject(std::shared_ptr<GameLoop>& game_loop, std::shared_ptr<Object> obj)
{
    game_loop->addUpdatableShape(obj->getShapeBase());
    game_loop->addUpdatableObject(obj);
}
