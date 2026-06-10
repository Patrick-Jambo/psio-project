#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Vector2f& position, const int& character_size, const std::string& text, const sf::Font& font);

    void update(const sf::Vector2i& mouse_pos);
    bool clicked(const sf::Vector2i& mouse_pos, const sf::Event& event);
    bool is_mouse_over() const { return hovered; }
    void draw(sf::RenderWindow& window);

    void set_position(const sf::Vector2f& position);
    float get_width() const;

    void set_text_string(const std::string& new_text);
    void set_text_colors(const sf::Color& default_c, const sf::Color& hover_c);
    void set_text_outlines(const sf::Color& default_outline, const sf::Color& hover_outline, float thickness);

private:
    sf::Text text;
    sf::RectangleShape bounds;
    bool hovered = false;

    sf::Color text_default_color = sf::Color::White;
    sf::Color text_hover_color   = sf::Color::Red;

    sf::Color outline_default_color = sf::Color::Transparent;
    sf::Color outline_hover_color   = sf::Color::Transparent;
    float outline_thickness = 0.0f;

    void apply_visual_state();
    void recalculate_bounds();
};