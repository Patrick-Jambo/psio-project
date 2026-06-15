#include "../Game.hpp"
#include "GoalArea.hpp"

GoalArea::GoalArea(const sf::FloatRect &bounds) : Area(bounds)
{
    debug_hitbox_color = sf::Color(0,0,0,125);
}

void GoalArea::on_enter(Game& game) {
    if (game.can_advance_level()) {
        game.advance_level();
    }
}

void GoalArea::debug_hitbox() {

}