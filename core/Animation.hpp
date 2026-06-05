#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(sf::Sprite& target_sprite, float frame_duration = 0.15f);

    void add_frame(const sf::IntRect& rect);
    void add_frame_line(int start_x, int start_y, int width, int height, int count, int spacing = 0);
    void update(float dt);
    void reset();

private:
    sf::Sprite& sprite;
    std::vector<sf::IntRect> frames;
    size_t current_frame = 0;
    float timer = 0;
    float frame_duration;
};