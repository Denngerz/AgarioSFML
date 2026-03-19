#include "GameLoop.h"

#include <optional>
#include <ranges>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/CameraComponent.h"
#include "../Input/InputManager.h"
#include "../Object/Object.h"
#include "../Object/Pawn/Pawn.h"
#include "../Object/Widget/Widget.h"
#include "../Time/Time.h"
#include "../Interfaces/ICameraProvider.h"
#include "../World/World.h"

GameLoop::GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle, bool showGrid)
    : showGrid(showGrid), currentInputEvent(sf::Event::KeyPressed{})
{
    time = std::make_shared<Time>();
    
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({ windowWidth, windowHeight }),
        windowTitle,
        sf::Style::Titlebar | sf::Style::Close
    );

    window->setFramerateLimit(60);

    inputManager = std::make_shared<InputManager>();
}

void GameLoop::initialize()
{
    objectFactory = std::make_shared<ObjectFactory>(shared_from_this());

    world = objectFactory->createObject<World>();

    activeView = std::make_shared<sf::View>(sf::Vector2f(0,0), sf::Vector2f(1920,1080));

    if (showGrid)
    {
        buildGrid();
    }
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
    refreshActiveCamera();
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

    if (showGrid)
    {
        window->draw(gridLines);
    }

    for (const auto& shape : drawableShapes | std::views::filter([](const auto& s) { return s != nullptr; }))
    {
        window->draw(*shape);
    }

    window->setView(window->getDefaultView());

    for (const auto& drawable : widgetDrawables | std::views::filter([](const auto& d) { return d != nullptr; }))
    {
        window->draw(*drawable);
    }

    window->display();
}

void GameLoop::refreshActiveCamera()
{
    auto validProviders = cameraProviders | std::views::filter([](const auto& obj) { return obj != nullptr; });

    auto it = std::ranges::find_if(validProviders, [this](const auto& obj) {
        auto provider = std::dynamic_pointer_cast<ICameraProvider>(obj);
        if (!provider || !provider->getIsMainProvider())
            return false;
        auto camComp = provider->getCameraComponent();
        return camComp && currentCamera != camComp;
    });

    if (it != validProviders.end())
    {
        auto provider = std::dynamic_pointer_cast<ICameraProvider>(*it);
        currentCamera = provider->getCameraComponent();
        currentCamera->setOwnerPawn(std::dynamic_pointer_cast<Pawn>(*it));
        activeView = std::make_shared<sf::View>(currentCamera->getCurrentPosition(), sf::Vector2f(1920,1080));
        window->setView(*activeView);
    }
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
    for (const auto& obj : tickableObjects| std::views::filter([](const auto& o) { return o && !o->getIsActive(); }))
    {
        const auto& shape = obj->getShapeBase();
        if (shape)
        {
            drawableShapes.remove(shape);
        }

        if (auto widget = std::dynamic_pointer_cast<Widget>(obj))
        {
            widgetDrawables.remove(widget->getDrawable());
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

    if (auto widget = std::dynamic_pointer_cast<Widget>(obj))
    {
        widgetDrawables.add(widget->getDrawable());
    }

    if (obj->getIsTickable())
    {
        tickableObjects.add(obj);
    }

    if (world && obj != std::static_pointer_cast<Object>(world))
    {
        world->registerObject(obj);
    }

    if (std::dynamic_pointer_cast<ICameraProvider>(obj))
    {
        cameraProviders.add(obj);
        refreshActiveCamera();
    }
}

void GameLoop::removeObject(const std::shared_ptr<Object>& obj)
{
    if (!obj)
    {
        return;
    }

    drawableShapes.remove(obj->getShapeBase());

    if (auto widget = std::dynamic_pointer_cast<Widget>(obj))
    {
        widgetDrawables.remove(widget->getDrawable());
    }

    tickableObjects.remove(obj);

    if (std::dynamic_pointer_cast<ICameraProvider>(obj))
    {
        cameraProviders.remove(obj);
        refreshActiveCamera();
    }
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

std::shared_ptr<World> GameLoop::getWorld() const
{
    return world;
}

void GameLoop::buildGrid()
{
    const float mapExtent = 2000.0f;
    const float cellSize = 100.0f;
    const sf::Color gridColor(100, 100, 100);

    gridLines = sf::VertexArray(sf::PrimitiveType::Lines);

    for (float x = -mapExtent; x <= mapExtent; x += cellSize)
    {
        gridLines.append(sf::Vertex{sf::Vector2f{x, -mapExtent}, gridColor});
        gridLines.append(sf::Vertex{sf::Vector2f{x, mapExtent}, gridColor});
    }

    for (float y = -mapExtent; y <= mapExtent; y += cellSize)
    {
        gridLines.append(sf::Vertex{sf::Vector2f{-mapExtent, y}, gridColor});
        gridLines.append(sf::Vertex{sf::Vector2f{mapExtent, y}, gridColor});
    }
}
