#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f start, sf::Vector2f end, float speed, ResourceManager &resources) {
    start_pos = start;
    end_pos = end;
    target_pos = end;
    this->speed = speed;

    const sf::Texture& texture = resources.get_texture("assets/img/enemy.png");
    enemy_sprite.setTexture(texture);

    animator = std::make_unique<Animation>(enemy_sprite);
    animator->add_frame_line(0,0,302,379,6,5);
    enemy_sprite.setOrigin(302 / 2.0f, 379 / 2.0f);
    setScale(0.125f, 0.125f);
    setPosition(start_pos);
    HITBOX_HEIGHT_PCT = 0.8f;
}

void Enemy::update(float dt, const TileMap &level_map) {
    sf::Vector2f current_pos = getPosition();
    animator->update(dt);

    sf::Vector2f direction = target_pos - current_pos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.0f) {
        direction /= distance;

        float move_dist = speed * dt;

        if (move_dist >= distance) {
            setPosition(target_pos);
            target_pos = (target_pos == end_pos) ? start_pos : end_pos;
        } else {
            move(direction * move_dist);
        }
    }
}

sf::FloatRect Enemy::get_hitbox() const {
    sf::FloatRect bounds = enemy_sprite.getLocalBounds();
    float hitbox_w = bounds.width * HITBOX_WIDTH_PCT;
    float hitbox_h = bounds.height * HITBOX_HEIGHT_PCT;

    sf::FloatRect local_hitbox(
        -enemy_sprite.getOrigin().x + (bounds.width - hitbox_w) / 2.0f,
        -enemy_sprite.getOrigin().y + (bounds.height - hitbox_h) / 2.0f,
        hitbox_w,
        hitbox_h
    );
    return getTransform().transformRect(local_hitbox);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(enemy_sprite, states);

    if (HITBOX_DEBUG) {
        draw_debug_hitbox(target);
    }
}
