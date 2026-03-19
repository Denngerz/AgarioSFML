#pragma once
#include "../../../Core/Object/Widget/Widget.h"
#include <vector>

class Unit;

class LeaderBoard: public Widget
{
public:
    LeaderBoard(std::shared_ptr<ObjectFactory> objFactory, const std::vector<std::shared_ptr<Unit>>& inUnits);

    const std::shared_ptr<sf::Drawable>& getDrawable() const override;

    void update(float deltaTime) override;

private:
    const std::vector<std::shared_ptr<Unit>>& units;

    std::shared_ptr<sf::Drawable> drawable;

    std::shared_ptr<sf::Text> leaderBoardText;

    sf::Font font;

    void refreshText();
};
