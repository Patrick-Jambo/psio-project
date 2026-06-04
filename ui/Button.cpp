#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const int& character_size, const std::string &text, const sf::Font &font) {
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(character_size);
    this->text.setFillColor(default_color);

    this->text.setPosition(position);

    bounds.setPosition(position);
    bounds.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height * 1.5));
    bounds.setFillColor(sf::Color::Transparent);
}

bool Button::mouse_hover(const sf::Vector2i& mouse_pos) {
    return bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos));
}

void Button::update(const sf::Vector2i& mouse_pos) {
    if (mouse_hover(mouse_pos)) {
        text.setFillColor(hover_color);
    } else {
        text.setFillColor(default_color);
    }
}

bool Button::clicked(const sf::Vector2i& mouse_pos, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        return mouse_hover(mouse_pos);
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

void Button::set_text_outline(const sf::Color &outline_color, const float& thickness) {
    text.setOutlineColor(outline_color);
    text.setOutlineThickness(thickness);
}
