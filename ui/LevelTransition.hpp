#pragma once
#include <SFML/Graphics.hpp>
#include "../core/ResourceManager.hpp"

class LevelTransition {
public:
    LevelTransition(ResourceManager& resources);

    void start(const std::string& text);
    bool update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Text display_text;
    sf::RectangleShape background;
    float timer = 0.0f;
    const float DURATION = 1.0f;
};