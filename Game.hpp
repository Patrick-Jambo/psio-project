#pragma once
#include <SFML/Graphics.hpp>
#include "core/ResourceManager.hpp"
#include "ui/Button.hpp"
#include "ui/Settings.hpp"
#include "ui/MainMenu.hpp"
#include "objects/Player.hpp"
#include "core/TileMap.hpp"
#include "objects/Enemy.hpp"
#include "objects/Collectible.hpp"
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    void handle_events();
    void update(float dt);
    void render();
    void init_level(const int& level_num);

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

    int current_level = 1;
    TileMap level_map;
    Game_state game_state = Game_state::MAIN_MENU;

    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Collectible>> collectibles;
    std::unique_ptr<Settings> game_settings;

    void check_game_collisions();

};