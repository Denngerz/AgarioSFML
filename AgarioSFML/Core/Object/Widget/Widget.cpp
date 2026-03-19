#include "Widget.h"

Widget::Widget(std::shared_ptr<ObjectFactory> objFactory): Object(objFactory)
{
}

const std::shared_ptr<sf::Shape>& Widget::getShapeBase() const
{
    return Object::getShapeBase();
}