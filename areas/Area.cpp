#include "Area.hpp"
#include "../ui/Settings.hpp"


void Area::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (Settings::hitboxes_enabled) {
        sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
        rect.setPosition(bounds.left, bounds.top);
        rect.setFillColor(debug_hitbox_color);
        rect.setOutlineColor(sf::Color(debug_hitbox_color.r, debug_hitbox_color.g, debug_hitbox_color.b, 255));
        rect.setOutlineThickness(1.0f);

        target.draw(rect, states);
    }
}