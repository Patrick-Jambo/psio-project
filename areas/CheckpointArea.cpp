#include "CheckpointArea.hpp"
#include "../Game.hpp"

void CheckpointArea::on_enter(Game& game) {
    game.get_player().set_respawn_position(respawn_position);
}