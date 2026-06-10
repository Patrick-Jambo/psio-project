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

    bool is_god_mode() const { return god_mode_enabled; }
    bool is_show_hitboxes() const { return hitboxes_enabled; }

    bool any_button_hovered() const;

    static bool music_enabled;
    static bool god_mode_enabled;
    static bool hitboxes_enabled;

private:
    sf::Music& music_ref;

    std::unique_ptr<Button> music_button;
    std::unique_ptr<Button> god_mode_button;
    std::unique_ptr<Button> hitboxes_button;

    void update_button_visuals();
};