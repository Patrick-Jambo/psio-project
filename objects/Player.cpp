#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#define DEBUG_HITBOX

Player::Player(sf::Vector2f start_pos, ResourceManager& resources) :
animator(player_sprite) {
    const sf::Texture& player_texture = resources.get_texture("assets/img/player.png");
    player_sprite.setTexture(player_texture);

    animator.add_frame_line(0,0,319,434,6,5);

    player_sprite.setOrigin(319 / 2.0f, 434 / 2.0f);
    setScale(0.2f, 0.2f);
    setPosition(start_pos);

}

void Player::handle_input() {
    velocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y = SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x = SPEED;
}

void Player::update(float dt, const TileMap& level_map) {
    handle_input();
    animator.update(dt);

    // --- DEBUG ---
    static float timer = 0.0f;
    timer += dt;
    if (timer >= 1.0f) {
        timer = 0.0f;
        sf::FloatRect hb = get_hitbox();
        printf("Hitbox: pos=(%.1f, %.1f)  size=(%.1f x %.1f)\n",
               hb.left, hb.top, hb.width, hb.height);
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
#ifdef DEBUG_HITBOX
    sf::FloatRect hb = get_hitbox();
    sf::RectangleShape debug_rect(sf::Vector2f(hb.width, hb.height));
    debug_rect.setPosition(hb.left, hb.top);
    debug_rect.setFillColor(sf::Color(255, 0, 0, 80));
    debug_rect.setOutlineColor(sf::Color::Red);
    debug_rect.setOutlineThickness(1.0f);
    target.draw(debug_rect);
#endif
}