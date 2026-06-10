#include "GameRules.hpp"
#include "../core/Config.hpp"
#include "../core/Utils.hpp"

GameRules::GameRules(ResourceManager& resources) {
    const sf::Font& pixeled_font = resources.get_font("assets/fonts/Pixeled.ttf");
    const sf::Font& pixelzone_font = resources.get_font("assets/fonts/Pixelzone.ttf");
    sf::Color outline_color(0, 0, 0);

    background_sprite.setTexture(resources.get_texture("assets/img/background_blurred.png"));

    rules_title.setFont(pixeled_font);
    rules_title.setString("HOW TO PLAY");
    rules_title.setCharacterSize(60);
    rules_title.setFillColor(sf::Color(255, 100, 0));
    rules_title.setOutlineColor(outline_color);
    rules_title.setOutlineThickness(4.0f);
    rules_title.setPosition(Utils::get_centered_x(rules_title.getGlobalBounds().width), 80.0f);

    rules_content.setFont(pixelzone_font);
    rules_content.setString("You are the little flame. Avoid the water enemies and burn the green leaves.\n Once you have collected all of the leaves, move to the green zone to complete the level.\nSome levels consist of intermediary white zones that act as checkpoints.\n You must complete all 10 levels in order to finishthe game.\n Your final screen will reflect how many times you have died; the less, the better.");

    rules_content.setCharacterSize(58);
    rules_content.setFillColor(sf::Color::White);
    rules_content.setOutlineColor(outline_color);
    rules_content.setOutlineThickness(3.0f);
    rules_content.setLineSpacing(1.2f);
    rules_content.setPosition(Utils::get_centered_x(rules_content.getGlobalBounds().width), 190.0f);

    return_prompt.setFont(pixeled_font);
    return_prompt.setString("PRESS [ENTER] TO PLAY  /  [ESC] TO RETURN");
    return_prompt.setCharacterSize(24);
    return_prompt.setFillColor(sf::Color(200, 200, 200));
    return_prompt.setOutlineColor(outline_color);
    return_prompt.setOutlineThickness(2.0f);
    return_prompt.setPosition(Utils::get_centered_x(return_prompt.getGlobalBounds().width), 620.0f);
}

void GameRules::handle_event(const sf::Event& event, bool& start_playing, bool& return_to_main_menu) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            start_playing = true;
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            return_to_main_menu = true;
        }
    }
}

void GameRules::draw(sf::RenderWindow& game_window) {
    game_window.draw(background_sprite);
    game_window.draw(rules_title);
    game_window.draw(rules_content);
    game_window.draw(return_prompt);
}