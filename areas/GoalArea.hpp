#pragma once
#include "../Game.hpp"


class GoalArea : public Area {
public:
    GoalArea(const sf::FloatRect& bounds);

    void on_enter(Game& game) override;
    void debug_hitbox() override;
};

