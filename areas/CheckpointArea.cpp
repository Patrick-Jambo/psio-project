#include "CheckpointArea.hpp"
#include "../Game.hpp"


CheckpointArea::CheckpointArea(const sf::FloatRect &bounds, const sf::Vector2f &respawn_pos) : Area(bounds)
{
    debug_hitbox_color = sf::Color(255,255,255,125);
}

void CheckpointArea::on_enter(Game& game) {
    game.get_player().set_respawn_position(respawn_position);
}

void CheckpointArea::debug_hitbox() {

}