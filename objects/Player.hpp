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

    void update(float dt, const TileMap& level_map);
    sf::FloatRect get_hitbox() const override;

private:
    const float SPEED = 400;
    const float HITBOX_WIDTH_PCT  = 0.93f;
    const float HITBOX_HEIGHT_PCT = 0.68f;

    sf::Sprite player_sprite;
    sf::Vector2f velocity;
    Animation animator;

    void handle_input();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};