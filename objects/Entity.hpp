#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../core/TileMap.hpp"
#include "../core/Animation.hpp"
#include <memory>

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity() = default;
    virtual ~Entity() = default;
    virtual void update(float dt, const TileMap& level_map) = 0;
    virtual sf::FloatRect get_hitbox() const = 0;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
    void draw_debug_hitbox(sf::RenderTarget& target) const;
    void log_hitbox(float dt);

    std::unique_ptr<Animation> animator;

    float HITBOX_WIDTH_PCT = 1.0f;
    float HITBOX_HEIGHT_PCT = 1.0f;

};