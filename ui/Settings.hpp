#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <memory>
#include "Button.hpp"

class Settings {
public:
    Settings(const sf::Font& font, sf::Music& bg_music);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event);
    void update(const sf::Vector2i& mouse_pos);
    void draw(sf::RenderWindow& window);

    bool is_god_mode() const { return god_mode; }
    bool is_show_hitboxes() const { return show_hitboxes; }

    bool any_button_hovered() const;

private:
    sf::Music& music_ref;

    std::unique_ptr<Button> music_button;
    std::unique_ptr<Button> god_mode_button;
    std::unique_ptr<Button> show_hitbox_button;
    std::unique_ptr<Button> level_selector_button;

    bool music_enabled = true;
    bool god_mode = false;
    bool show_hitboxes = true;

    void update_button_visuals();
};