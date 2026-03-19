#include "LeaderBoard.h"
#include <algorithm>
#include <ranges>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../../CirclePawn/Unit.h"

LeaderBoard::LeaderBoard(std::shared_ptr<ObjectFactory> objFactory, const std::vector<std::shared_ptr<Unit>>& inUnits)
    : Widget(objFactory),
      units(inUnits)
{
    font = sf::Font("resources/tuffy.ttf");

    leaderBoardText = std::make_shared<sf::Text>(font, "", 18);
    leaderBoardText->setFillColor(sf::Color::Black);
    leaderBoardText->setPosition(sf::Vector2f(10.0f, 10.0f));

    drawable = leaderBoardText;
}

const std::shared_ptr<sf::Drawable>& LeaderBoard::getDrawable() const
{
    return drawable;
}

void LeaderBoard::update(float deltaTime)
{
    Widget::update(deltaTime);
    refreshText();
}

void LeaderBoard::refreshText()
{
    auto activeUnits = units | std::views::filter([](const auto& unit) {
        return unit && unit->getIsActive();
    });

    std::vector<std::pair<std::string, float>> entries;

    for (const auto& unit : activeUnits)
    {
        std::string name = unit->getIsAIControlled() ? "Enemy" : "Player";
        entries.emplace_back(name, unit->getArea());
    }

    std::ranges::sort(entries, [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::ostringstream ss;
    ss << "Leaderboard\n";

    for (const auto& [name, area] : entries)
    {
        ss << name << " - " << static_cast<int>(area) << "\n";
    }

    leaderBoardText->setString(ss.str());
}
