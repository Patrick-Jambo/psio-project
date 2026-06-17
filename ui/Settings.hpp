#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <memory>
#include "Button.hpp"

class Settings {
public:
    Settings(const sf::Font& font, sf::Music& bg_music);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& should_close);
    void update(const sf::Vector2i& mouse_pos);
    void draw(sf::RenderWindow& window);

    bool is_god_mode() const { return god_mode_enabled; }
    bool is_show_hitboxes() const { return hitboxes_enabled; }

    bool any_button_hovered() const;

    static bool music_enabled;
    static bool sounds_enabled;
    static bool god_mode_enabled;
    static bool hitboxes_enabled;
    static float volume;

private:
    void update_volume_text(float current_y);

    sf::Music& music_ref;

    sf::RectangleShape window_background;
    sf::Text window_title;
    std::unique_ptr<Button> close_button;

    std::unique_ptr<Button> music_button;
    std::unique_ptr<Button> sounds_button;
    std::unique_ptr<Button> god_mode_button;
    std::unique_ptr<Button> hitboxes_button;

    std::unique_ptr<Button> vol_minus_btn;
    std::unique_ptr<Button> vol_plus_btn;
    sf::Text vol_display_text;
};