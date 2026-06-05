#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(sf::Vector2f start_pos, ResourceManager& resources) {
    const sf::Texture& player_texture = resources.get_texture("assets/img/player.png");
    player_sprite.setTexture(player_texture);

    // animacja
    animation_frames.push_back(sf::IntRect(157, 99, 319, 391));
    animation_frames.push_back(sf::IntRect(476, 99, 319, 391));
    animation_frames.push_back(sf::IntRect(795, 99, 319, 391));
    // reszta klatek, te nie są dobrz skalibrowane jeszcze
    player_sprite.setTextureRect(animation_frames[0]);
    player_sprite.setOrigin(319 / 2.0f, 391 / 2.0f);
    player_sprite.setScale(0.2f, 0.2f);
    setPosition(start_pos);

}

void Player::handle_input() {
    velocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y = SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x = SPEED;
}

void Player::update(float dt) {
    handle_input();
    move(velocity * dt);
    if (!animation_frames.empty()) {
        animation_timer += dt;
        if (animation_timer >= FRAME_DURATION) {
            animation_timer -= FRAME_DURATION;
            current_frame = (current_frame + 1) % animation_frames.size();
            player_sprite.setTextureRect(animation_frames[current_frame]);
        }
    }
}

sf::FloatRect Player::get_hitbox() const {
    return getTransform().transformRect(player_sprite.getLocalBounds());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(player_sprite, states);
}