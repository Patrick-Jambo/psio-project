#include "MainMenu.hpp"

MainMenu::MainMenu(ResourceManager &resources) {
    const sf::Font& main_font = resources.get_font("assets/fonts/Pixelmax-Regular.otf");
    game_title.setFont(main_font);
}
