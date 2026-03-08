#pragma once
#include <memory>

class CameraComponent;

class ICameraProvider
{
public:
    virtual std::shared_ptr<CameraComponent> getCameraComponent() = 0;
};
