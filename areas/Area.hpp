#pragma once
#include <SFML/Graphics.hpp>

class Area : public sf::Drawable {
public:
    Area(const sf::FloatRect& bounds) : bounds(bounds) {}
    virtual ~Area() = default;

    virtual void on_enter(class Game& game) = 0;

    virtual void debug_hitbox() = 0;

    const sf::FloatRect& get_bounds() const { return bounds; }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::FloatRect bounds;
    sf::Color debug_hitbox_color;
};