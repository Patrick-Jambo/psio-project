#pragma once
#include "Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f start, sf::Vector2f end, float speed, ResourceManager& resources);
    ~Enemy() override = default;

    void update(float dt, const TileMap &level_map) override;
    sf::FloatRect get_hitbox() const override;

private:
    sf::Sprite enemy_sprite;

    sf::Vector2f start_pos;
    sf::Vector2f end_pos;
    sf::Vector2f target_pos;
    float speed;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};