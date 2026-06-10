#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Game.hpp"


class CheckpointArea : public Area {
public:
    CheckpointArea(const sf::FloatRect& bounds, const sf::Vector2f& respawn_pos);

    void on_enter(Game& game) override;
    void debug_hitbox() override;

private:
    sf::Vector2f respawn_position;
};
