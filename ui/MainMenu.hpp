#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../core/ResourceManager.hpp"
#include "Button.hpp"

class MainMenu {
public:
    MainMenu(ResourceManager& resources);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& start_menu_flag, bool& open_settings_flag, bool& open_selector_flag);
    void update(const sf::Vector2i mouse_pos);
    void draw(sf::RenderWindow& game_window);

    const Button& get_play_button() const { return *play_button; }
    const Button& get_settings_button() const { return *settings_button; }
    const Button& get_selector_button() const { return *selector_button; }

private:
    sf::Text game_title;
    std::unique_ptr<Button> play_button;
    std::unique_ptr<Button> settings_button;
    std::unique_ptr<Button> selector_button; // Nowy przycisk
    sf::Sprite background_sprite;
};