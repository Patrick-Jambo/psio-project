#pragma once
#include <SFML/Graphics.hpp>
#include "../core/ResourceManager.hpp"

class LevelStatsDisplay {
public:
    LevelStatsDisplay(ResourceManager& resources);

    void update(float total_seconds, int death_count);
    void draw(sf::RenderWindow& window);

private:
    sf::Text death_text;
    sf::Text time_text;

    std::string format_time(float total_seconds);
};