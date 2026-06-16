#pragma once
#include <SFML/Graphics.hpp>
#include "../core/ResourceManager.hpp"

class EndGameScreen {
public:
    EndGameScreen(ResourceManager& resources);
    void setup_final_scores(const sf::Font& font, int total_deaths, float total_time,
                    bool is_death_rec, bool is_time_rec,
                    int current_record_deaths, float current_record_time,
                    bool is_selector_run);

    void handle_event(const sf::Event& event, bool& return_to_menu);
    void draw(sf::RenderWindow& game_window);

private:
    sf::Sprite background_sprite;
    sf::Text congrats_title;
    sf::Text final_deaths_text;
    sf::Text final_time_text;
    sf::Text return_prompt;
    sf::Text selector_warning_text;

    std::string format_time(float total_seconds);
};