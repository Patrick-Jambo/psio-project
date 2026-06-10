#pragma once
#include <SFML/Graphics.hpp>
#include "../core/ResourceManager.hpp"

class GameRules {
public:
    GameRules(ResourceManager& resources);

    void handle_event(const sf::Event& event, bool& start_playing, bool& return_to_main_menu);
    void draw(sf::RenderWindow& game_window);

private:
    sf::Sprite background_sprite;
    sf::Text rules_title;
    sf::Text rules_content;
    sf::Text return_prompt;
};