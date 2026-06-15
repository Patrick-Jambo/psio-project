#include "Enemy.hpp"
#include <cmath>
#include "../ui/Settings.hpp"


Enemy::Enemy(std::vector<sf::Vector2f> pts, float speed, ResourceManager &resources, EnemyMoveMode mode) {
    waypoints = std::move(pts);
    this->speed = speed;
    move_mode = mode;

    if (!waypoints.empty()) setPosition(waypoints[0]);
    if (waypoints.size() > 1) current_target_idx = 1;

    const sf::Texture& texture = resources.get_texture("assets/img/enemy.png");
    enemy_sprite.setTexture(texture);
    animator = std::make_unique<Animation>(enemy_sprite);
    animator->add_frame_line(0,0,200,200,9,5);
    enemy_sprite.setOrigin(200 / 2.0f, 200 / 2.0f);
    setScale(0.16f, 0.16f);
}


Enemy::Enemy(sf::Vector2f center, float radius, float angular_speed, ResourceManager& resources) {
    center_pos = center;
    this->radius = radius;
    speed = angular_speed;
    move_mode = EnemyMoveMode::Circular;

    setPosition(sf::Vector2f(center.x + radius, center.y));

    const sf::Texture& texture = resources.get_texture("assets/img/enemy.png");
    enemy_sprite.setTexture(texture);
    animator = std::make_unique<Animation>(enemy_sprite);
    animator->add_frame_line(0,0,200,200,9,5);
    enemy_sprite.setOrigin(200 / 2.0f, 200 / 2.0f);
    setScale(0.16f, 0.16f);
}

void Enemy::update(float dt, const TileMap &level_map) {
    animator->update(dt);

    switch (move_mode) {
        case EnemyMoveMode::PingPong:
        case EnemyMoveMode::Path: {
            if (waypoints.size() < 2) return;

            sf::Vector2f current_pos = getPosition();
            sf::Vector2f target_pos = waypoints[current_target_idx];
            sf::Vector2f direction = target_pos - current_pos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance > 0.0f) {
                float move_dist = speed * dt;

                if (move_dist >= distance) {
                    setPosition(target_pos);

                    if (move_mode == EnemyMoveMode::Path) {
                        current_target_idx = (current_target_idx + 1) % waypoints.size();
                    } else {
                        if (current_target_idx == waypoints.size() - 1) {
                            direction_step = -1;
                        } else if (current_target_idx == 0) {
                            direction_step = 1;
                        }
                        current_target_idx += direction_step;
                    }
                } else {
                    move((direction / distance) * move_dist);
                }
            }
            break;
        }

        case EnemyMoveMode::Circular: {
            current_angle += speed * dt;

            if (current_angle > 6.2831853f) current_angle -= 6.2831853f;

            float new_x = center_pos.x + radius * std::cos(current_angle);
            float new_y = center_pos.y + radius * std::sin(current_angle);

            setPosition(sf::Vector2f(new_x, new_y));
            break;
        }
    }
}

sf::FloatRect Enemy::get_hitbox() const {
    sf::FloatRect bounds = enemy_sprite.getLocalBounds();

    float HITBOX_WIDTH_PCT = 0.5f;
    float HITBOX_HEIGHT_PCT = 0.5f;

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

    if (Settings::hitboxes_enabled) {
        draw_debug_hitbox(target);
    }
}