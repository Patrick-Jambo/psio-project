#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const int& character_size, const std::string &text_str, const sf::Font &font) {
    text.setFont(font);
    text.setString(text_str);
    text.setCharacterSize(character_size);
    text.setFillColor(text_default_color);
    text.setPosition(position);

    bounds.setPosition(position);
    bounds.setSize(sf::Vector2f(text.getLocalBounds().width, text.getGlobalBounds().height * 1.5f));
    bounds.setFillColor(sf::Color::Transparent);
}

void Button::update(const sf::Vector2i& mouse_pos) {
    hovered = bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos));
    apply_visual_state();
}

void Button::apply_visual_state() {
    if (hovered) {
        text.setFillColor(text_hover_color);
        text.setOutlineColor(outline_hover_color);
    } else {
        text.setFillColor(text_default_color);
        text.setOutlineColor(outline_default_color);
    }
    text.setOutlineThickness(outline_thickness);
}

bool Button::clicked(const sf::Vector2i& mouse_pos, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        return hovered;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(bounds);
    window.draw(text);
}

void Button::set_position(const sf::Vector2f& position) {
    text.setPosition(position);
    bounds.setPosition(position);
}

float Button::get_width() const {
    return text.getGlobalBounds().width;
}

void Button::set_text_string(const std::string& new_text) {
    text.setString(new_text);
    // Recalculates if string length changed
    bounds.setSize(sf::Vector2f(text.getLocalBounds().width, text.getGlobalBounds().height * 1.5f));
}

void Button::set_text_colors(const sf::Color& default_c, const sf::Color& hover_c) {
    text_default_color = default_c;
    text_hover_color = hover_c;
    apply_visual_state();
}

void Button::set_text_outlines(const sf::Color& default_outline, const sf::Color& hover_outline, float thickness) {
    outline_default_color = default_outline;
    outline_hover_color = hover_outline;
    outline_thickness = thickness;
    apply_visual_state();
}