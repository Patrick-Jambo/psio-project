#include "../ui/EndGameScreen.hpp"
#include "../core/Config.hpp"
#include "../core/Utils.hpp"
#include <iomanip>
#include <sstream>

EndGameScreen::EndGameScreen(ResourceManager& resources) {
    background_sprite.setTexture(resources.get_texture("assets/img/background_blurred.png"));

    const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
    sf::Color outline_color = sf::Color::Black;

    congrats_title.setFont(font);
    congrats_title.setString("CONGRATULATIONS!");
    congrats_title.setCharacterSize(60);
    congrats_title.setFillColor(sf::Color(0, 255, 100));
    congrats_title.setOutlineColor(outline_color);
    congrats_title.setOutlineThickness(5.0f);
    congrats_title.setPosition(Utils::get_centered_x(congrats_title.getGlobalBounds().width), 120.0f);

    return_prompt.setFont(font);
    return_prompt.setString("PRESS ENTER OR ESC TO RETURN TO MENU");
    return_prompt.setCharacterSize(24);
    return_prompt.setFillColor(sf::Color(200, 200, 200));
    return_prompt.setOutlineColor(outline_color);
    return_prompt.setOutlineThickness(2.0f);
    return_prompt.setPosition(Utils::get_centered_x(return_prompt.getGlobalBounds().width), 580.0f);
}

void EndGameScreen::setup_final_scores(const sf::Font& font, int total_deaths, float total_time, bool is_death_rec, bool is_time_rec, int current_record_deaths, float current_record_time) {
    sf::Color outline_color = sf::Color::Black;

    final_deaths_text.setFont(font);
    final_deaths_text.setCharacterSize(30);
    final_deaths_text.setOutlineColor(outline_color);
    final_deaths_text.setOutlineThickness(3.0f);

    if (is_death_rec) {
        final_deaths_text.setString("DEATHS: " + std::to_string(total_deaths) + " (NEW RECORD!)");
        final_deaths_text.setFillColor(sf::Color::Yellow);
    } else {
        // Zamiana -1 na kreskę
        std::string death_rec_str = (current_record_deaths == -1) ? "-" : std::to_string(current_record_deaths);

        final_deaths_text.setString("DEATHS: " + std::to_string(total_deaths) + "  (BEST: " + death_rec_str + ")");
        final_deaths_text.setFillColor(sf::Color::White);
    }
    final_deaths_text.setPosition(Utils::get_centered_x(final_deaths_text.getGlobalBounds().width), 260.0f);

    final_time_text.setFont(font);
    final_time_text.setCharacterSize(30);
    final_time_text.setOutlineColor(outline_color);
    final_time_text.setOutlineThickness(3.0f);

    if (is_time_rec) {
        final_time_text.setString("TIME: " + format_time(total_time) + " (NEW RECORD!)");
        final_time_text.setFillColor(sf::Color::Yellow);
    } else {
        // Zamiana -1 na kreskę
        std::string time_rec_str = (current_record_time == -1.0f) ? "-" : format_time(current_record_time);

        final_time_text.setString("TIME: " + format_time(total_time) + "  (BEST: " + time_rec_str + ")");
        final_time_text.setFillColor(sf::Color::White);
    }
    final_time_text.setPosition(Utils::get_centered_x(final_time_text.getGlobalBounds().width), 360.0f);
}

void EndGameScreen::handle_event(const sf::Event& event, bool& return_to_menu) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
            return_to_menu = true;
        }
    }
}

void EndGameScreen::draw(sf::RenderWindow& game_window) {
    game_window.draw(background_sprite);
    game_window.draw(congrats_title);
    game_window.draw(final_deaths_text);
    game_window.draw(final_time_text);
    game_window.draw(return_prompt);
}

std::string EndGameScreen::format_time(float total_seconds) {
    int minutes = static_cast<int>(total_seconds) / 60;
    int seconds = static_cast<int>(total_seconds) % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}