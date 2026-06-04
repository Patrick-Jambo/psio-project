#pragma once
#include <SFML/Graphics.hpp>

class   Button {
public:
    Button(const sf::Vector2f& position, const int& character_size, const std::string& text, const sf::Font& font);

    void update(const sf::Vector2i& mouse_pos);
    bool clicked(const sf::Vector2i& mouse_pos, const sf::Event& event);
    bool mouse_hover(const sf::Vector2i& mouse_pos);
    void draw(sf::RenderWindow& window);

    void set_position(const sf::Vector2f& position);
    float get_width() const;

    void set_text_outline(const sf::Color& outline_color, const float& thickness);

private:
    sf::Text text;
    sf::RectangleShape bounds;
    sf::Color default_color = sf::Color::White;
    sf::Color hover_color = sf::Color::Red;
};