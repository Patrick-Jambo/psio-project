#pragma once

class Area {
public:
    Area(const sf::FloatRect& bounds) : bounds(bounds) {}
    virtual ~Area() = default;

    virtual void on_enter(class Game& game) = 0;

    const sf::FloatRect& get_bounds() const { return bounds; }

protected:
    sf::FloatRect bounds;
};