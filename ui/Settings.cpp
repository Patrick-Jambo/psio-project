#include "Settings.hpp"
#include <iostream>

Settings::Settings(const sf::Font& font, sf::Music& bg_music) : music_ref(bg_music) {
    int char_size = 24;
    float current_x = 20.0f; // left margin
    float pos_y = 15.0f;     // top margin
    float spacing = 80.0f;   // gap between

    music_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, "MUSIC: ON", font);
    current_x += music_button->get_width() + spacing;

    god_mode_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, "GOD MODE: OFF", font);
    current_x += god_mode_button->get_width() + spacing;

    show_hitbox_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, "HITBOXES: ON", font);
    current_x += show_hitbox_button->get_width() + spacing;

    level_selector_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, "SKIP LEVEL", font);

    music_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    music_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    god_mode_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    god_mode_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    show_hitbox_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    show_hitbox_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    level_selector_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    level_selector_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);
}

void Settings::handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event) {
    if (music_button->clicked(mouse_pos, event)) {
        music_enabled = !music_enabled;
        if (music_enabled) {
            music_ref.play();
            music_button->set_text_string("MUSIC: ON");
            music_button->set_text_colors(sf::Color::White, sf::Color::Yellow);
        } else {
            music_ref.pause();
            music_button->set_text_string("MUSIC: OFF");
            music_button->set_text_colors(sf::Color::White, sf::Color::Red);
        }
    }
}

void Settings::update(const sf::Vector2i& mouse_pos) {
    music_button->update(mouse_pos);
    god_mode_button->update(mouse_pos);
    show_hitbox_button->update(mouse_pos);
    level_selector_button->update(mouse_pos);
}

void Settings::draw(sf::RenderWindow& window) {
    music_button->draw(window);
    god_mode_button->draw(window);
    show_hitbox_button->draw(window);
    level_selector_button->draw(window);
}

bool Settings::any_button_hovered() const {
    return (music_button && music_button->is_mouse_over()) ||
           (god_mode_button && god_mode_button->is_mouse_over()) ||
           (show_hitbox_button && show_hitbox_button->is_mouse_over()) ||
           (level_selector_button && level_selector_button->is_mouse_over());
}