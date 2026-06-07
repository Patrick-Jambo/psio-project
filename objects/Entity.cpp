#include "Entity.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

void Entity::draw_debug_hitbox(sf::RenderTarget& target) const {
    sf::FloatRect hb = get_hitbox();
    sf::RectangleShape debug_rect(sf::Vector2f(hb.width, hb.height));
    debug_rect.setPosition(hb.left, hb.top);
    debug_rect.setFillColor(sf::Color(255, 0, 0, 80));
    debug_rect.setOutlineColor(sf::Color::Red);
    debug_rect.setOutlineThickness(1.0f);
    target.draw(debug_rect);
}

void Entity::log_hitbox(float dt) {
    static float timer = 0.0f;
    timer += dt;
    if (timer >= 1.0f) {
        timer = 0.0f;
        sf::FloatRect hb = get_hitbox();
        printf("Hitbox: pos=(%.1f, %.1f)  size=(%.1f x %.1f)\n",
               hb.left, hb.top, hb.width, hb.height);
    }
}
