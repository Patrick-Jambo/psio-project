#include "CheckpointArea.hpp"
#include "../Game.hpp"

CheckpointArea::CheckpointArea(const sf::FloatRect &bounds, const sf::Vector2f &respawn_pos, ResourceManager& resources)
    : Area(bounds), respawn_position(respawn_pos)
{
    debug_hitbox_color = sf::Color(255, 255, 255, 125);
    campfire_sprite.setTexture(resources.get_texture("assets/img/campfire.png"));

    campfire_sprite.setOrigin(270 / 2.0f, 375 / 2.0f);
    campfire_sprite.setScale(0.3f, 0.3f);

    campfire_sprite.setPosition(respawn_position);

    animator = std::make_unique<Animation>(campfire_sprite, 0.15f, false);
    animator->add_frame(sf::IntRect(0, 0, 270, 375));
}

void CheckpointArea::on_enter(Game& game) {
    if (campfire_state == CampfireState::UNLIT) {
        game.get_player().set_respawn_position(respawn_position);

        campfire_state = CampfireState::IGNITING;
        animator->reset();
        animator = std::make_unique<Animation>(campfire_sprite, 0.15f, false);
        animator->add_frame_line(275, 0, 270, 375, 2,5);
    }
}

void CheckpointArea::update(float dt) {
    if (!animator) return;

    animator->update(dt);
    if (campfire_state == CampfireState::IGNITING && animator->is_finished()) {
        campfire_state = CampfireState::BURNING;

        // zapętlona animacja palenia 3 klatki i loop
        animator = std::make_unique<Animation>(campfire_sprite, 0.15f, true);
        animator->add_frame_line(825, 0, 270, 375, 3,5);
    }
}

void CheckpointArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(campfire_sprite, states);

    // draw z klasy bazowej żeby w razie czego dorysować hitbox
    Area::draw(target, states);
}

void CheckpointArea::debug_hitbox() {}