#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

enum class InputTriggerType
{
    Pressed,
    Released,
    Held
};

struct InputMapping
{
    std::string actionName;
    std::vector<sf::Keyboard::Key> inputKeys;
};

struct InputMappingContext
{
    std::vector<InputMapping> inputMappings;
};

class InputManager
{
public:
    InputManager();
    
    void updateCurrentFrameInputEvents(const std::vector<sf::Event>& inputEvents);
    void processCurrentFrameInputEvents();

    void setInputMappingContext(const InputMappingContext& newContext);

    void bindAction(const std::string& actionName, InputTriggerType triggerType, std::function<void()> callback);

    bool isActionPressed(const std::string& actionName) const;

private:
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool doesActionContainKey(const std::string& actionName, sf::Keyboard::Key key) const;

private:
    std::vector<sf::Event> currentFrameInputEvents;
    InputMappingContext currentInputMappingContext;

    std::unordered_map<sf::Keyboard::Key, bool> keyStates;
    std::vector<sf::Keyboard::Key> justPressedKeys;
    std::vector<sf::Keyboard::Key> justReleasedKeys;

    std::unordered_map<std::string, std::vector<std::function<void()>>> pressedCallbacks;
    std::unordered_map<std::string, std::vector<std::function<void()>>> releasedCallbacks;
    std::unordered_map<std::string, std::vector<std::function<void()>>> heldCallbacks;
};