#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../core/ResourceManager.hpp"
#include "Button.hpp"

class MainMenu {
public:
    MainMenu(ResourceManager& resources);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& start_menu_flag, bool& open_settings_flag);
    void update(const sf::Vector2i mouse_pos);
    void draw(sf::RenderWindow& game_window);

    const Button& get_play_button() const { return *play_button; }
    const Button& get_settings_button() const { return *settings_button; } // Nowy getter dla zmiany kursora

private:
    sf::Text game_title;
    std::unique_ptr<Button> play_button;
    std::unique_ptr<Button> settings_button; // Nowy przycisk
    sf::Sprite background_sprite;
};