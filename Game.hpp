#pragma once
#include <SFML/Graphics.hpp>
#include "core/ResourceManager.hpp"

class Game {
public:
    Game();
    void run();

private:
    void handle_events();
    void update(float dt);
    void render();

    sf::RenderWindow game_window;
    const int game_window_width = 1280;
    const int game_window_height = 720;

    sf::Clock game_clock;
    ResourceManager resources;

    enum class Game_state {
        MAIN_MENU,
        END_MENU,
        PLAYING,
        PAUSED
    };

    Game_state game_state_ = Game_state::MAIN_MENU;
};