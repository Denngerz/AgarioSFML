#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>

class Pawn;

class CameraComponent
{
public:
    CameraComponent(sf::Vector2f offset, float zoom);

    void setOwnerPawn(std::shared_ptr<Pawn> newOwner);

    void updatePosition();

    float getRealZoomValue();

    float getZoomValue();

    void setZoomValue(float newValue);

    sf::Vector2f getCurrentPosition();

    bool getShouldUpdateView();

    void setShouldUpdateView(bool newValue);

private:
    sf::Vector2f currentPosition;

    bool shouldUpdateView;

    sf::Vector2f currentOffset;

    float zoomValue;

    float realZoomValue;

    std::weak_ptr<Pawn> owner;
};
