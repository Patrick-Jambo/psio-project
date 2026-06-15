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
    game_title.setPosition(game_title_x, 150);
    game_title.setOutlineColor(sf::Color::Black);
    game_title.setOutlineThickness(5);

    // Przycisk PLAY (Y = 330)
    play_button = std::make_unique<Button>(sf::Vector2f(0, 330), 65, "PLAY", main_font);
    play_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    play_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 5);
    play_button->set_position(sf::Vector2f(Utils::get_centered_x(play_button->get_width()), 330));

    // Przycisk SETTINGS umieszczony pod Play (Y = 470)
    settings_button = std::make_unique<Button>(sf::Vector2f(0, 470), 45, "SETTINGS", main_font);
    settings_button->set_text_colors(sf::Color::White, sf::Color(255,152,2));
    settings_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 4);
    settings_button->set_position(sf::Vector2f(Utils::get_centered_x(settings_button->get_width()), 470));

    background_sprite.setTexture(resources.get_texture("assets/img/background.png"));
}

void MainMenu::handle_event(const sf::Vector2i &mouse_pos, const sf::Event &event, bool &start_menu_flag, bool &open_settings_flag) {
    if (play_button->clicked(mouse_pos, event)) {
        start_menu_flag = true;
    }
    if (settings_button->clicked(mouse_pos, event)) {
        open_settings_flag = true;
    }
}

void MainMenu::update(const sf::Vector2i mouse_pos) {
    play_button->update(mouse_pos);
    settings_button->update(mouse_pos);
}

void MainMenu::draw(sf::RenderWindow &game_window) {
    game_window.draw(background_sprite);
    game_window.draw(game_title);
    play_button->draw(game_window);
    settings_button->draw(game_window); // Rysujemy przycisk ustawień
}