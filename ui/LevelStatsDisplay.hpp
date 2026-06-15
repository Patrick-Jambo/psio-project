#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../core/ResourceManager.hpp"
#include "Button.hpp"

class LevelStatsDisplay {
public:
    LevelStatsDisplay(ResourceManager& resources);

    void update(float level_time, int deaths, int collected, int total_col, int current_lv, const sf::Vector2i& mouse_pos);
    bool handle_menu_click(const sf::Vector2i& mouse_pos, const sf::Event& event);
    void draw(sf::RenderWindow& window);

    const Button& get_menu_button() const { return *menu_button; }

private:
    sf::Text death_text;
    sf::Text time_text;
    sf::Text leaves_text;
    sf::Text level_text;

    std::unique_ptr<Button> menu_button;

    std::string format_time(float total_seconds);
};