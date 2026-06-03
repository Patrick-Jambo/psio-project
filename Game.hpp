#pragma once
#include <SFML/Graphics.hpp>
#include "core/ResourceManager.hpp"
#include "ui/Button.hpp"
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    void handle_events();
    void update(float dt);
    void render();


    const std::string GAME_NAME = "WORLDS HARDEST SPARK";
    const int GAME_FRAME_RATE = 60;
    const int game_window_width = 1280;
    const int game_window_height = 720;

    sf::Clock game_clock;
    ResourceManager resources;
    sf::RenderWindow game_window;
    sf::Text game_title;
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
    std::unique_ptr<Button> play_button;
};