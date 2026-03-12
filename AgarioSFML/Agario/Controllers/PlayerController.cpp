#include "PlayerController.h"

#include "../Game.h"
#include "../CirclePawn/Unit.h"
#include "../../Core/Input/InputManager.h"

PlayerController::PlayerController(std::shared_ptr<ObjectFactory> objFactory, std::shared_ptr<InputManager> input): Controller(objFactory, input)
{
    controlledUnit = nullptr;
}

void PlayerController::possessPawn(std::shared_ptr<Pawn> targetObj)
{
    Controller::possessPawn(targetObj);

    if (auto objAsUnit = std::dynamic_pointer_cast<Unit>(targetObj))
    {
        controlledUnit = objAsUnit;
    }
}

void PlayerController::unpossessPawn()
{
    Controller::unpossessPawn();

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

    inputManager->bindAction("Swap", InputTriggerType::Pressed, [this]()
   {
       if (controlledUnit)
       {
           controlledUnit->becomeUnpossesed();
           controlledUnit->setIsAIControlled(true);
           controlledUnit = nullptr;
       }
        
       auto newUnit = gamemode.lock()->getRandomUnit();
       if (newUnit)
       {
           possessPawn(newUnit);
       }
   });

    inputManager->bindAction("Sprint", InputTriggerType::Pressed, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->sprint();
    });

    inputManager->bindAction("Sprint", InputTriggerType::Released, [this]()
    {
        if (!controlledUnit)
        {
            return;
        }
        controlledUnit->stopSprint();
    });
}

void PlayerController::setGamemode(std::shared_ptr<Game> newGamemode)
{
    gamemode = newGamemode;
}
