#pragma once
#include <SFML/Graphics.hpp>
#include "core/ResourceManager.hpp"
#include "ui/Button.hpp"
#include "ui/MainMenu.hpp"
#include "objects/Player.hpp"
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    void handle_events();
    void update(float dt);
    void render();

    sf::Clock game_clock;
    ResourceManager resources;
    sf::RenderWindow game_window;
    sf::Music bg_music;

    sf::Cursor default_cursor;
    sf::Cursor hand_cursor;

    enum class Game_state {
        MAIN_MENU,
        END_MENU,
        PLAYING,
        PAUSED
    };

    Game_state game_state = Game_state::MAIN_MENU;
    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<Player> player;
};