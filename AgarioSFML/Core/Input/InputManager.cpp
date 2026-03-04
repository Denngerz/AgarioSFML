#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::updateCurrentFrameInputEvents(const std::vector<sf::Event>& newFrameInputEvents)
{
    currentFrameInputEvents = newFrameInputEvents;

    processCurrentFrameInputEvents();
}

void InputManager::setInputMappingContext(const InputMappingContext& newInputMappingContext)
{
    currentInputMappingContext = newInputMappingContext;
}

void InputManager::processCurrentFrameInputEvents()
{
    if (currentInputMappingContext.inputMappings.empty())
    {
        return;
    }

    for (const sf::Event& currentEvent : currentFrameInputEvents)
    {
        for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
        {
            for (const InputKey& currentKey : currentMapping.inputKeys)
            {
                if (IsKeyboardEventMatchingInputKey(currentEvent, currentKey))
                {
                    // action matched
                }
            }
        }
    }
}

bool InputManager::IsKeyboardEventMatchingInputKey(const sf::Event& currentEvent, const InputKey& currentKey) const
{
    if (const auto* keyPressedEvent = currentEvent.getIf<sf::Event::KeyPressed>())
    {
        return keyPressedEvent->code == currentKey.keyValue;
    }

    if (const auto* keyReleasedEvent = currentEvent.getIf<sf::Event::KeyReleased>())
    {
        return keyReleasedEvent->code == currentKey.keyValue;
    }

    return false;
}