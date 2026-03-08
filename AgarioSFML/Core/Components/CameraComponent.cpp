#include "CameraComponent.h"

#include "../Object/Pawn/Pawn.h"

CameraComponent::CameraComponent(sf::Vector2f offset, float zoom)
    : currentOffset(offset),
    zoomValue(zoom),
    shouldUpdateView(false)
{
    currentPosition = sf::Vector2f(0.0f,0.0f);

    realZoomValue = zoom;
}

void CameraComponent::setOwnerPawn(std::shared_ptr<Pawn> newOwner)
{
    if (newOwner)
    {
        owner = newOwner;
        updatePosition();
    }
}

void CameraComponent::updatePosition()
{
    auto lockedOwner = owner.lock();
    if (!lockedOwner)
    {
        return;
    }

    const auto& shape = lockedOwner->getShapeBase();
    if (!shape)
    {
        return;
    }

    currentPosition = shape->getPosition() + currentOffset;
}

float CameraComponent::getRealZoomValue()
{
    return realZoomValue;
}

float CameraComponent::getZoomValue()
{
    return zoomValue;
}

void CameraComponent::setZoomValue(float newValue)
{
    zoomValue = newValue / realZoomValue;

    realZoomValue = newValue;

    setShouldUpdateView(true);
}

sf::Vector2f CameraComponent::getCurrentPosition()
{
    return currentPosition;
}

bool CameraComponent::getShouldUpdateView()
{
    return shouldUpdateView;
}

void CameraComponent::setShouldUpdateView(bool newValue)
{
    shouldUpdateView = newValue;
}
