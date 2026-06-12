#include "Settings.hpp"
#include <iostream>
#include "../objects/Entity.hpp"

bool Settings::music_enabled = true;
bool Settings::god_mode_enabled = false;
bool Settings::hitboxes_enabled = false;

Settings::Settings(const sf::Font& font, sf::Music& bg_music) : music_ref(bg_music) {
    int char_size = 18;
    float current_x = 20.0f; // left margin
    float pos_y = 15.0f;     // top margin
    float spacing = 80.0f;   // gap between

    // --- DOPASOWANIE NAPISÓW DO ZAOBSERWOWANEGO STANU Z JSON ---
    std::string music_txt = Settings::music_enabled ? "MUSIC: ON" : "MUSIC: OFF";
    std::string god_txt = Settings::god_mode_enabled ? "GOD MODE: ON" : "GOD MODE: OFF";
    std::string hit_txt = Settings::hitboxes_enabled ? "HITBOXES: ON" : "HITBOXES: OFF";

    music_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, music_txt, font);
    current_x += music_button->get_width() + spacing;

    god_mode_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, god_txt, font);
    current_x += god_mode_button->get_width() + spacing;

    hitboxes_button = std::make_unique<Button>(sf::Vector2f(current_x, pos_y), char_size, hit_txt, font);
    current_x += hitboxes_button->get_width() + spacing;

    music_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    music_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    god_mode_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    god_mode_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    hitboxes_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    hitboxes_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    if (!Settings::music_enabled) {
        music_button->set_text_colors(sf::Color::White, sf::Color::Red);
    }
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

    if (god_mode_button->clicked(mouse_pos, event)) {
        if (!god_mode_enabled) {
            god_mode_button->set_text_string("GOD MODE: ON");
        } else {
            god_mode_button->set_text_string("GOD MODE: OFF");
        }
        god_mode_enabled = !god_mode_enabled;
    }

    if (hitboxes_button->clicked(mouse_pos, event)) {
        if (!hitboxes_enabled) {
            hitboxes_button->set_text_string("HITBOXES: ON");
        } else {
            hitboxes_button->set_text_string("HITBOXES: OFF");
        }
        hitboxes_enabled = !hitboxes_enabled;
    }

}

void Settings::update(const sf::Vector2i& mouse_pos) {
    music_button->update(mouse_pos);
    god_mode_button->update(mouse_pos);
    hitboxes_button->update(mouse_pos);
}

void Settings::draw(sf::RenderWindow& window) {
    music_button->draw(window);
    god_mode_button->draw(window);
    hitboxes_button->draw(window);
}

bool Settings::any_button_hovered() const {
    return (music_button && music_button->is_mouse_over()) ||
           (god_mode_button && god_mode_button->is_mouse_over()) ||
           (hitboxes_button && hitboxes_button->is_mouse_over());
}