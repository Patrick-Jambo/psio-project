#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"
#include "../core/Animation.hpp"
#include "../core/TileMap.hpp"

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(sf::Vector2f start_pos, ResourceManager& resources);
    ~Player() override = default;

    sf::FloatRect get_hitbox() const override;
    void update(float dt, const TileMap& level_map) override;
    void set_respawn_position(const sf::Vector2f& new_respawn) { respawn_position = new_respawn; }
    void respawn() { setPosition(respawn_position); }

private:
    const float SPEED = 400;

    sf::Sprite player_sprite;
    sf::Vector2f velocity;
    sf::Vector2f respawn_position;

    void handle_input();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};