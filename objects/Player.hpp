#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"
#include "../core/Animation.hpp"

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(sf::Vector2f start_pos, ResourceManager& resources);
    ~Player() override = default;

    void update(float dt) override;
    sf::FloatRect get_hitbox() const override;

private:
    const float SPEED = 400;

    sf::Sprite player_sprite;
    sf::Vector2f velocity;
    Animation animator;

    void handle_input();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};