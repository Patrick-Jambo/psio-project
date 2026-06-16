#include "MainMenu.hpp"
#include "../core/Config.hpp"
#include "../core/Utils.hpp"

MainMenu::MainMenu(ResourceManager &resources) {
    const sf::Font& main_font = resources.get_font("assets/fonts/Pixeled.ttf");

    game_title.setFont(main_font);
    game_title.setString(Config::GAME_NAME);
    game_title.setCharacterSize(80);
    game_title.setFillColor(sf::Color(255, 100, 0));

    float game_title_x = Utils::get_centered_x(game_title.getGlobalBounds().width);
    game_title.setPosition(game_title_x, 110);
    game_title.setOutlineColor(sf::Color::Black);
    game_title.setOutlineThickness(5);

    //PLAY
    play_button = std::make_unique<Button>(sf::Vector2f(0, 310), 55, "PLAY", main_font);
    play_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    play_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 4);
    play_button->set_position(sf::Vector2f(Utils::get_centered_x(play_button->get_width()), 310));

    //SETTINGS
    settings_button = std::make_unique<Button>(sf::Vector2f(0, 420), 35, "SETTINGS", main_font);
    settings_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    settings_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 3);
    settings_button->set_position(sf::Vector2f(Utils::get_centered_x(settings_button->get_width()), 420));

    //LV SELECTOR
    selector_button = std::make_unique<Button>(sf::Vector2f(0, 520), 35, "LEVEL SELECTOR", main_font);
    selector_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    selector_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 3);
    selector_button->set_position(sf::Vector2f(Utils::get_centered_x(selector_button->get_width()), 510));

    background_sprite.setTexture(resources.get_texture("assets/img/background.png"));
}

void MainMenu::handle_event(const sf::Vector2i &mouse_pos, const sf::Event &event, bool &start_menu_flag, bool &open_settings_flag, bool &open_selector_flag) {
    if (play_button->clicked(mouse_pos, event)) start_menu_flag = true;
    if (settings_button->clicked(mouse_pos, event)) open_settings_flag = true;
    if (selector_button->clicked(mouse_pos, event)) open_selector_flag = true;
}

void MainMenu::update(const sf::Vector2i mouse_pos) {
    play_button->update(mouse_pos);
    settings_button->update(mouse_pos);
    selector_button->update(mouse_pos);
}

void MainMenu::draw(sf::RenderWindow &game_window) {
    game_window.draw(background_sprite);
    game_window.draw(game_title);
    play_button->draw(game_window);
    settings_button->draw(game_window);
    selector_button->draw(game_window);
}