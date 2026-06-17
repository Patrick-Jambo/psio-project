#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../ui/Settings.hpp"
#include <cmath>

Player::Player(sf::Vector2f start_pos, ResourceManager& resources) {
    set_respawn_position(start_pos);

    const sf::Texture& player_texture = resources.get_texture("assets/img/player_2.png");
    player_sprite.setTexture(player_texture);

    animator = std::make_unique<Animation>(player_sprite);
    animator->add_frame_line(0,0,300,300,6,5);

    player_sprite.setOrigin(300 / 2.0f, 300 / 2.0f);
    setScale(0.145f, 0.145f);
    setPosition(start_pos);
}

void Player::handle_input() {
    velocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += 1;

    if (velocity.x != 0 || velocity.y != 0) {
        auto length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = (velocity.x / length) * SPEED;
        velocity.y = (velocity.y / length) * SPEED;
    }
}

void Player::update(float dt, const TileMap& level_map) {
    handle_input();
    animator->update(dt);

    if (Settings::hitboxes_enabled) {
        log_hitbox(dt);
    }


    if (velocity.x != 0.0f) {
        sf::Vector2f old_pos = getPosition();
        move(velocity.x * dt, 0.0f);
        if (level_map.check_wall_collision(get_hitbox())) {
            setPosition(old_pos.x, getPosition().y);
        }
    }

    if (velocity.y != 0.0f) {
        sf::Vector2f old_pos = getPosition();
        move(0.0f, velocity.y * dt);
        if (level_map.check_wall_collision(get_hitbox())) {
            setPosition(getPosition().x, old_pos.y);
        }
    }
}

sf::FloatRect Player::get_hitbox() const {
    sf::FloatRect bounds = player_sprite.getLocalBounds();

    float w = bounds.width;
    float h = bounds.height;

    float hitbox_w = w * HITBOX_WIDTH_PCT;
    float hitbox_h = h * HITBOX_HEIGHT_PCT;

    float local_x = -player_sprite.getOrigin().x + (w - hitbox_w) / 2.0f;
    float local_y = -player_sprite.getOrigin().y + h - hitbox_h;

    sf::FloatRect local_hitbox(local_x, local_y, hitbox_w, hitbox_h);

    return getTransform().transformRect(local_hitbox);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(player_sprite, states);

    if (Settings::hitboxes_enabled) {
        draw_debug_hitbox(target);
    }
}