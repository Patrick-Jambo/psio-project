#include "Collectible.hpp"
#include <cmath>

Collectible::Collectible(sf::Vector2f pos, ResourceManager& resources) {
    const sf::Texture& tex = resources.get_texture("assets/img/leaf.png");
    sprite.setTexture(tex);

    sf::Vector2f size(tex.getSize());
    sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);

    sprite.setTextureRect(sf::IntRect(0,0,293,347));

    HITBOX_WIDTH_PCT = 1.05f;
    HITBOX_HEIGHT_PCT = 0.87f;

    setPosition(pos);
}

void Collectible::update(float dt, const TileMap& level_map) {
    if (collected) return;
    bounce_timer += dt * 5.0f;
    sprite.setPosition(0.0f, std::sin(bounce_timer) * 4.0f);
}

sf::FloatRect Collectible::get_hitbox() const {
    sf::FloatRect bounds = sprite.getLocalBounds();
    float hitbox_w = bounds.width * HITBOX_WIDTH_PCT;
    float hitbox_h = bounds.height * HITBOX_HEIGHT_PCT;

    sf::FloatRect local_hitbox(
        -sprite.getOrigin().x + (bounds.width - hitbox_w) / 2.0f,
        -sprite.getOrigin().y + (bounds.height - hitbox_h) / 2.0f,
        hitbox_w,
        hitbox_h
    );
    return getTransform().transformRect(local_hitbox);
}

void Collectible::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (collected) return;

    states.transform *= getTransform();
    target.draw(sprite, states);

    if (HITBOX_DEBUG) {
        draw_debug_hitbox(target);
    }
}