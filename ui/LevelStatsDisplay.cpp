#include "LevelStatsDisplay.hpp"
#include "../core/Config.hpp"
#include <iomanip>
#include <sstream>

LevelStatsDisplay::LevelStatsDisplay(ResourceManager& resources) {
    const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
    int char_size = 18;
    sf::Color text_color = sf::Color::White;
    sf::Color outline_color(0, 0, 0, 200);
    float outline_thickness = 2.0f;

    death_text.setFont(font);
    death_text.setCharacterSize(char_size);
    death_text.setFillColor(text_color);
    death_text.setOutlineColor(outline_color);
    death_text.setOutlineThickness(outline_thickness);
    death_text.setString("DEATHS: 0");

    time_text.setFont(font);
    time_text.setCharacterSize(char_size);
    time_text.setFillColor(text_color);
    time_text.setOutlineColor(outline_color);
    time_text.setOutlineThickness(outline_thickness);
    time_text.setString("TIME: 00:00");
}

void LevelStatsDisplay::update(float total_seconds, int death_count) {
    death_text.setString("DEATHS: " + std::to_string(death_count));
    time_text.setString("TIME: " + format_time(total_seconds));

    float right_margin = 20.0f; // right margin
    float pos_y = 15.0f;        // top margin
    float spacing = 50.0f;      // gap between

    float time_x = Config::WINDOW_WIDTH - right_margin - time_text.getGlobalBounds().width;
    time_text.setPosition(time_x, pos_y);

    float death_x = time_x - spacing - death_text.getGlobalBounds().width;
    death_text.setPosition(death_x, pos_y);
}

void LevelStatsDisplay::draw(sf::RenderWindow& window) {
    window.draw(death_text);
    window.draw(time_text);
}

std::string LevelStatsDisplay::format_time(float total_seconds) {
    // formats time to 00:00
    int minutes = static_cast<int>(total_seconds) / 60;
    int seconds = static_cast<int>(total_seconds) % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;

    return oss.str();
}