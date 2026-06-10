#pragma once
#include "../Game.hpp"
#include "GoalArea.hpp"

void GoalArea::on_enter(Game& game) {
    game.advance_level();
}