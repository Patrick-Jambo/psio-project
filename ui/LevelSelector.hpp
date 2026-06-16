#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.hpp"
#include "../core/ResourceManager.hpp"

class LevelSelector {
public:
    LevelSelector(ResourceManager& resources);

    void handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& should_close, int& selected_level);
    void update(const sf::Vector2i& mouse_pos);
    void draw(sf::RenderWindow& window);

    bool any_button_hovered() const;

private:
    sf::RectangleShape window_background;
    sf::Text window_title;
    std::unique_ptr<Button> close_button;
    std::vector<std::unique_ptr<Button>> level_buttons;
};