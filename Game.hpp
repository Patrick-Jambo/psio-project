#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void handle_events();
    void update(float dt);
    void render();

    sf::RenderWindow game_window;
    sf::Clock game_clock;

    enum class Game_state {
        MAIN_MENU,
        END_MENU,
        PLAYING,
        PAUSED
    };

    Game_state game_state_ = Game_state::MAIN_MENU;
};