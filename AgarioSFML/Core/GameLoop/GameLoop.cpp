#include "GameLoop.h"
#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/CameraComponent.h"
#include "../Input/InputManager.h"
#include "../Object/Object.h"
#include "../Object/Pawn/Pawn.h"
#include "../Time/Time.h"
#include "../Interfaces/ICameraProvider.h"

GameLoop::GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle)
    : currentInputEvent(sf::Event::KeyPressed{})
{
    time = std::make_shared<Time>();
    
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({ windowWidth, windowHeight }),
        windowTitle
    );

    window->setFramerateLimit(60);

    inputManager = std::make_shared<InputManager>();
}

void GameLoop::initialize()
{
    objectFactory = std::make_shared<ObjectFactory>(shared_from_this());
}

void GameLoop::runLoop()
{
    generate();

    while (!isEndGame())
    {
        processInput();
        logic();
        draw();
    }
}

void GameLoop::generate()
{
}

void GameLoop::processInput()
{
    std::vector<sf::Event> frameEvents;

    while (const std::optional event = window->pollEvent())
    {
        frameEvents.push_back(*event);
    }

    inputManager->updateCurrentFrameInputEvents(frameEvents);
}

void GameLoop::logic()
{
    time->update();
    updateObjects();
    updateObjectsCollision();
    cleanupInactiveObjects();
}

void GameLoop::draw() const
{
    updateWindow();
}

bool GameLoop::isEndGame() const
{
    return !window->isOpen();
}

void GameLoop::updateWindow() const
{
    window->clear(sf::Color::White);
    
    if (currentCamera && activeView)
    {
        currentCamera->updatePosition();
        activeView->setCenter(currentCamera->getCurrentPosition());

        if (currentCamera->getShouldUpdateView())
        {
            activeView->zoom(currentCamera->getZoomValue());
            currentCamera->setShouldUpdateView(false);
        }
        
        window->setView(*activeView);
    }

    for (const auto& shape : drawableShapes)
    {
        if (shape)
        {
            window->draw(*shape);
        }
    }

    window->display();
}

void GameLoop::updateActiveCamera(std::shared_ptr<ICameraProvider> newCam)
{
    activeView = std::make_shared<sf::View>(currentCamera->getCurrentPosition(), sf::Vector2f(1920, 1080));
    
    window->setView(*activeView.get());
}

void GameLoop::updateObjects()
{
    for (const auto& obj : tickableObjects)
    {
        if (obj && obj->getIsActive())
        {
            obj->update(time->deltaTime);
        }
    }
}

void GameLoop::updateObjectsCollision()
{
    for (auto firstIt = tickableObjects.begin(); firstIt != tickableObjects.end(); ++firstIt)
    {
        auto secondIt = firstIt;
        ++secondIt;

        for (; secondIt != tickableObjects.end(); ++secondIt)
        {
            std::shared_ptr<Object>& firstObject = *firstIt;
            std::shared_ptr<Object>& secondObject = *secondIt;

            if (!firstObject || !secondObject)
            {
                continue;
            }

            if (!firstObject->getIsActive() || !secondObject->getIsActive())
            {
                continue;
            }

            firstObject->checkCollisionWithObject(secondObject);
            secondObject->checkCollisionWithObject(firstObject);
        }
    }
}

void GameLoop::cleanupInactiveObjects()
{
    for (const auto& currentObject : tickableObjects)
    {
        if (!currentObject)
        {
            continue;
        }

        if (!currentObject->getIsActive())
        {
            const auto& shape = currentObject->getShapeBase();
            if (shape)
            {
                drawableShapes.remove(shape);
            }
        }
    }

    tickableObjects.clearIf(
        [](const std::shared_ptr<Object>& currentObject)
        {
            return !currentObject || !currentObject->getIsActive();
        });
}

void GameLoop::addObject(const std::shared_ptr<Object>& obj)
{
    if (!obj)
    {
        return;
    }

    drawableShapes.add(obj->getShapeBase());

    if (obj->getIsTickable())
    {
        tickableObjects.add(obj);
    }
    
    if (auto cam = std::dynamic_pointer_cast<ICameraProvider>(obj))
    if (auto cam = std::dynamic_pointer_cast<ICameraProvider>(obj))
    {
        if (cam->getCameraComponent())
        {
            currentCamera = cam->getCameraComponent();
            currentCamera->setOwnerPawn(std::dynamic_pointer_cast<Pawn>(obj));
            
            updateActiveCamera(cam);
        }
    }
}

void GameLoop::removeObject(const std::shared_ptr<Object>& obj)
{
    if (!obj)
    {
        return;
    }

    drawableShapes.remove(obj->getShapeBase());
    tickableObjects.remove(obj);
}

std::weak_ptr<sf::RenderWindow> GameLoop::getWindow() const
{
    return window;
}

std::shared_ptr<ObjectFactory> GameLoop::getFactory() const
{
    return objectFactory;
}

std::shared_ptr<InputManager> GameLoop::getInputManager() const
{
    return inputManager;
}
