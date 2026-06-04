#include "MainMenu.hpp"
#include "../core/Config.hpp"
#include "../core/Utils.hpp"

MainMenu::MainMenu(ResourceManager &resources) {
    const sf::Font& main_font = resources.get_font("assets/fonts/Pixelmax-Regular.otf");
    game_title.setFont(main_font);
    game_title.setString(Config::GAME_NAME);
    game_title.setCharacterSize(90);
    game_title.setFillColor(sf::Color(255, 100, 0));

    float game_title_x = Utils::get_centered_x(game_title.getGlobalBounds().width);
    game_title.setPosition(game_title_x, 150);
    game_title.setOutlineColor(sf::Color(0,0,0));
    game_title.setOutlineThickness(5);


    play_button = std::make_unique<Button>(sf::Vector2f(0, 350), 85, "PLAY", main_font);
    play_button->set_position(sf::Vector2f(Utils::get_centered_x(play_button->get_width()), 350));
    play_button->set_text_outline(sf::Color(0,0,0), 5);

    background_sprite.setTexture(resources.get_texture("assets/img/background.png"));

}

void MainMenu::handle_event(const sf::Vector2i &mouse_pos, const sf::Event &event, bool &start_menu_flag) {
    if (play_button->clicked(mouse_pos, event)) {
        start_menu_flag = true;
    }
}

void MainMenu::update(const sf::Vector2i mouse_pos) {
    play_button->update(mouse_pos);
}

void MainMenu::draw(sf::RenderWindow &game_window) {
    game_window.draw(background_sprite);
    game_window.draw(game_title);
    play_button->draw(game_window);
}

bool MainMenu::play_button_hover(const sf::Vector2i &mouse_pos) {
    return play_button->mouse_hover(mouse_pos);
}

