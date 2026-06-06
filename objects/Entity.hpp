#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void update(float dt, const TileMap& level_map) = 0;
    virtual sf::FloatRect get_hitbox() const = 0;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};