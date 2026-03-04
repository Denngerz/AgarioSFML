#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <string>
#include <unordered_map>

enum class ValueType
{
    Bool = 0,
    TwoDimensional = 1
};

enum class ValueModifier
{
    Negate = 0,
    SwizzleAxis = 1
};

struct InputAction
{
    std::string actionName;
    ValueType inputType;
};

struct InputKey
{
    sf::Keyboard::Key keyValue;
    std::vector<ValueModifier> valueModifiers;
};

struct InputMapping
{
    InputAction inputAction;
    std::vector<InputKey> inputKeys;
};

struct InputMappingContext
{
    std::vector<InputMapping> inputMappings;
};

class InputManager
{
public:
    InputManager();
    
    void updateCurrentFrameInputEvents(const std::vector<sf::Event>& newFrameInputEvents);

    void setInputMappingContext(const InputMappingContext& newInputMappingContext);

    void bindAction(const std::string& actionName, std::function<void()> callback);
    
    void triggerAction(const std::string& actionName);

private:
    std::vector<sf::Event> currentFrameInputEvents;

    InputMappingContext currentInputMappingContext;
    
    void processCurrentFrameInputEvents();
    
    bool IsKeyboardEventMatchingInputKey(const sf::Event& currentEvent, const InputKey& currentKey) const;

    std::unordered_map<std::string, std::vector<std::function<void()>>> actionCallbacks;
};
