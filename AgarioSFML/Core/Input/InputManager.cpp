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
            for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
            {
                if (IsKeyboardEventMatchingInputKey(currentEvent, currentKey))
                {
                    triggerAction(currentMapping.actionName);
                }
            }
        }
    }
}

bool InputManager::IsKeyboardEventMatchingInputKey(const sf::Event& currentEvent, const sf::Keyboard::Key& currentKey) const
{
    if (const auto* keyPressedEvent = currentEvent.getIf<sf::Event::KeyPressed>())
    {
        return keyPressedEvent->code == currentKey;
    }

    if (const auto* keyReleasedEvent = currentEvent.getIf<sf::Event::KeyReleased>())
    {
        return keyReleasedEvent->code == currentKey;
    }

    return false;
}

void InputManager::bindAction(const std::string& actionName, std::function<void()> callback)
{
    actionCallbacks[actionName].push_back(std::move(callback));
}

void InputManager::triggerAction(const std::string& actionName)
{
    auto foundCallbacks = actionCallbacks.find(actionName);
    if (foundCallbacks == actionCallbacks.end())
    {
        return;
    }

    for (const auto& callback : foundCallbacks->second)
    {
        callback();
    }
}