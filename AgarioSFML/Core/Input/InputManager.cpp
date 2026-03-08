#include "InputManager.h"

InputManager::InputManager()
{
    InputMappingContext testContext
    {
            {
                { "MoveUp",    { sf::Keyboard::Key::W } },
                { "MoveDown",  { sf::Keyboard::Key::S } },
                { "MoveLeft",  { sf::Keyboard::Key::A } },
                { "MoveRight", { sf::Keyboard::Key::D } },
                { "Swap",      { sf::Keyboard::Key::F } }
            }
    };

    currentInputMappingContext = testContext;
}

void InputManager::updateCurrentFrameInputEvents(const std::vector<sf::Event>& inputEvents)
{
    currentFrameInputEvents = inputEvents;

    justPressedKeys.clear();
    justReleasedKeys.clear();

    for (const sf::Event& currentEvent : currentFrameInputEvents)
    {
        if (const auto* keyPressedEvent = currentEvent.getIf<sf::Event::KeyPressed>())
        {
            const sf::Keyboard::Key pressedKey = keyPressedEvent->code;

            if (!isKeyPressed(pressedKey))
            {
                keyStates[pressedKey] = true;
                justPressedKeys.push_back(pressedKey);
            }
        }

        if (const auto* keyReleasedEvent = currentEvent.getIf<sf::Event::KeyReleased>())
        {
            const sf::Keyboard::Key releasedKey = keyReleasedEvent->code;

            if (isKeyPressed(releasedKey))
            {
                keyStates[releasedKey] = false;
                justReleasedKeys.push_back(releasedKey);
            }
        }
    }

    processCurrentFrameInputEvents();
}

void InputManager::processCurrentFrameInputEvents()
{
    for (const sf::Keyboard::Key& pressedKey : justPressedKeys)
    {
        for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
        {
            for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
            {
                if (currentKey == pressedKey)
                {
                    auto foundCallbacks = pressedCallbacks.find(currentMapping.actionName);
                    if (foundCallbacks != pressedCallbacks.end())
                    {
                        for (const auto& callback : foundCallbacks->second)
                        {
                            callback();
                        }
                    }

                    break;
                }
            }
        }
    }

    for (const auto& [key, isPressed] : keyStates)
    {
        if (!isPressed)
        {
            continue;
        }

        for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
        {
            for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
            {
                if (currentKey == key)
                {
                    auto foundCallbacks = heldCallbacks.find(currentMapping.actionName);
                    if (foundCallbacks != heldCallbacks.end())
                    {
                        for (const auto& callback : foundCallbacks->second)
                        {
                            callback();
                        }
                    }

                    break;
                }
            }
        }
    }

    for (const sf::Keyboard::Key& releasedKey : justReleasedKeys)
    {
        for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
        {
            for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
            {
                if (currentKey == releasedKey)
                {
                    auto foundCallbacks = releasedCallbacks.find(currentMapping.actionName);
                    if (foundCallbacks != releasedCallbacks.end())
                    {
                        for (const auto& callback : foundCallbacks->second)
                        {
                            callback();
                        }
                    }

                    break;
                }
            }
        }
    }
}

void InputManager::setInputMappingContext(const InputMappingContext& newContext)
{
    currentInputMappingContext = newContext;
}

void InputManager::bindAction(const std::string& actionName, InputTriggerType triggerType, std::function<void()> callback)
{
    switch (triggerType)
    {
    case InputTriggerType::Pressed:
        pressedCallbacks[actionName].push_back(std::move(callback));
        break;

    case InputTriggerType::Released:
        releasedCallbacks[actionName].push_back(std::move(callback));
        break;

    case InputTriggerType::Held:
        heldCallbacks[actionName].push_back(std::move(callback));
        break;
    }
}

bool InputManager::isActionPressed(const std::string& actionName) const
{
    for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
    {
        if (currentMapping.actionName != actionName)
        {
            continue;
        }

        for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
        {
            auto foundKey = keyStates.find(currentKey);
            if (foundKey != keyStates.end() && foundKey->second)
            {
                return true;
            }
        }
    }

    return false;
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
{
    auto foundKey = keyStates.find(key);

    if (foundKey == keyStates.end())
    {
        return false;
    }

    return foundKey->second;
}

bool InputManager::doesActionContainKey(const std::string& actionName, sf::Keyboard::Key key) const
{
    for (const InputMapping& currentMapping : currentInputMappingContext.inputMappings)
    {
        if (currentMapping.actionName != actionName)
        {
            continue;
        }

        for (const sf::Keyboard::Key& currentKey : currentMapping.inputKeys)
        {
            if (currentKey == key)
            {
                return true;
            }
        }
    }

    return false;
}