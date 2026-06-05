#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(sf::Vector2f start_pos, ResourceManager& resources) :
animator(player_sprite) {
    const sf::Texture& player_texture = resources.get_texture("assets/img/player.png");
    player_sprite.setTexture(player_texture);

    animator.add_frame_line(0,0,319,434,6,5);


    player_sprite.setOrigin(319 / 2.0f, 334 / 2.0f);
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
    animator.update(dt);
}

sf::FloatRect Player::get_hitbox() const {
    return getTransform().transformRect(player_sprite.getLocalBounds());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(player_sprite, states);
}