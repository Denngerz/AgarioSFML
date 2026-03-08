#include "PlayerController.h"

#include "../Game.h"
#include "../Unit/Unit.h"
#include "../../Core/Input/InputManager.h"

PlayerController::PlayerController(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input): Controller(objFactory, input)
{
    controlledUnit = nullptr;
}

void PlayerController::possessObject(std::shared_ptr<Object> targetObj)
{
    Controller::possessObject(targetObj);

    if (auto objAsUnit = std::dynamic_pointer_cast<Unit>(targetObj))
    {
        controlledUnit = objAsUnit;
    }
}

void PlayerController::unpossessObject()
{
    Controller::unpossessObject();

    controlledUnit = nullptr;
}

void PlayerController::beginPlay()
{
    Controller::beginPlay();

    inputManager->bindAction("MoveUp", InputTriggerType::Held, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->moveInDirection(sf::Vector2f(0, -1));
    });

    inputManager->bindAction("MoveDown", InputTriggerType::Held, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->moveInDirection(sf::Vector2f(0, 1));
    });

    inputManager->bindAction("MoveLeft", InputTriggerType::Held, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->moveInDirection(sf::Vector2f(-1, 0));
    });

    inputManager->bindAction("MoveRight", InputTriggerType::Held, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->moveInDirection(sf::Vector2f(1, 0));
    });
}

void PlayerController::setGamemode(std::shared_ptr<Game> newGamemode)
{
    gamemode = newGamemode;
}
