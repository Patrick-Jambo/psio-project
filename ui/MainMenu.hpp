#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../core/ResourceManager.hpp"
#include "Button.hpp"

class MainMenu {
public:
    MainMenu(ResourceManager& resources);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& start_menu_flag);
    void update(const sf::Vector2i mouse_pos);
    void draw(sf::RenderWindow& game_window);
    bool play_button_hover(const sf::Vector2i& mouse_pos);

private:
    sf::Text game_title;
    std::unique_ptr<Button> play_button;
    sf::Sprite background_sprite;
};