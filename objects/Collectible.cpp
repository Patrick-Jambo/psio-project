#include "Collectible.hpp"
#include <cmath>
#include "../ui/Settings.hpp"
Collectible::Collectible(sf::Vector2f pos, ResourceManager& resources) {
    const sf::Texture& tex = resources.get_texture("assets/img/leaf.png");
    sprite.setTexture(tex);

    sprite.setOrigin(293.0f / 2.0f, 347.0f / 2.0f);

    sprite.setTextureRect(sf::IntRect(0,0,293,347));
    setScale(0.109f, 0.092f);
    setPosition(pos);
}

void Collectible::update(float dt, const TileMap& level_map) {
    if (state == State::FINISHED) return;

    if (state == State::IDLE) {
        bounce_timer += dt * 5.0f;
        sprite.setPosition(0.0f, std::sin(bounce_timer) * 4.0f);
    }

    else if (state == State::BURNING) {
        if (animator) {
            animator->update(dt);

            if (animator->is_finished()) {
                state = State::FINISHED;
            }
        }
    }
}

sf::FloatRect Collectible::get_hitbox() const {
    if (state != State::IDLE) return sf::FloatRect(0, 0, 0, 0);

    sf::FloatRect bounds = sprite.getLocalBounds();
    float hitbox_w = bounds.width * HITBOX_WIDTH_PCT;
    float hitbox_h = bounds.height * HITBOX_HEIGHT_PCT;

    sf::FloatRect local_hitbox(
        -sprite.getOrigin().x + (bounds.width - hitbox_w) / 2.0f,
        -sprite.getOrigin().y + (bounds.height - hitbox_h) / 2.0f + sprite.getPosition().y,
        hitbox_w,
        hitbox_h
    );

    return getTransform().transformRect(local_hitbox);
}

void Collectible::collect() {
    if (state != State::IDLE) return;
    state = State::BURNING;

    animator = std::make_unique<Animation>(sprite, 0.1f, false);
    animator->add_frame_line(0, 0, 293, 347, 6, 5);
}

void Collectible::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (state == State::FINISHED) return;

    states.transform *= getTransform();
    target.draw(sprite, states);

    if (Settings::hitboxes_enabled && state == State::IDLE) {
        draw_debug_hitbox(target);
    }
}