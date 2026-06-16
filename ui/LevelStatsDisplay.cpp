#include "LevelStatsDisplay.hpp"
#include "../core/Config.hpp"
#include <sstream>
#include <iomanip>

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

    leaves_text.setFont(font);
    leaves_text.setCharacterSize(char_size);
    leaves_text.setFillColor(text_color);
    leaves_text.setOutlineColor(outline_color);
    leaves_text.setOutlineThickness(outline_thickness);

    level_text.setFont(font);
    level_text.setCharacterSize(char_size);
    level_text.setFillColor(text_color);
    level_text.setOutlineColor(outline_color);
    level_text.setOutlineThickness(outline_thickness);
    level_text.setString("LV: 1 / 10");

    menu_button = std::make_unique<Button>(sf::Vector2f(0, 0), char_size, "MAIN MENU", font);
    menu_button->set_text_colors(sf::Color::White, sf::Color(255, 152, 2));
    menu_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);
}

void LevelStatsDisplay::update(float total_seconds, int deaths, int collected, int total_col, int current_level, const sf::Vector2i& mouse_pos) {
    death_text.setString("DEATHS: " + std::to_string(deaths));
    time_text.setString("TIME: " + format_time(total_seconds));
    leaves_text.setString("LEAVES: " + std::to_string(collected) + " / " + std::to_string(total_col));
    level_text.setString("LEVEL: " + std::to_string(current_level) + " / 10");

    float left_margin = 20.0f;
    float right_margin = 20.0f;
    float pos_y = 15.0f;
    float spacing = 50.0f;

    level_text.setPosition(left_margin, pos_y);

    float menu_btn_x = level_text.getPosition().x + level_text.getGlobalBounds().width + 40.0f;

    menu_button->set_position(sf::Vector2f(menu_btn_x, pos_y));
    menu_button->update(mouse_pos);

    float time_x = Config::WINDOW_WIDTH - right_margin - time_text.getGlobalBounds().width;
    time_text.setPosition(time_x, pos_y);

    float death_x = time_x - spacing - death_text.getGlobalBounds().width;
    death_text.setPosition(death_x, pos_y);

    float leaves_x = death_x - spacing - leaves_text.getGlobalBounds().width;
    leaves_text.setPosition(leaves_x, pos_y);
}

bool LevelStatsDisplay::handle_menu_click(const sf::Vector2i& mouse_pos, const sf::Event& event) {
    return menu_button->clicked(mouse_pos, event);
}

void LevelStatsDisplay::draw(sf::RenderWindow& window) {
    window.draw(death_text);
    window.draw(time_text);
    window.draw(leaves_text);
    window.draw(level_text);
    menu_button->draw(window);
}

std::string LevelStatsDisplay::format_time(float total_seconds) {
    // formatuje czas do postaci MM:SS
    int minutes = static_cast<int>(total_seconds) / 60;
    int seconds = static_cast<int>(total_seconds) % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;

    return oss.str();
}