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
#include "areas/Area.hpp"
#include "ui/LevelStatsDisplay.hpp"
#include "ui/GameRules.hpp"
#include <memory>

class Game {
public:
    Game();
    void run();
    Player& get_player() { return *player; }
    void advance_level();

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
        RULES,
        END_MENU,
        PLAYING,
        PAUSED
    };

    int current_level = 1;
    int death_counter = 0;
    float level_time = 0.0f;

    TileMap level_map;
    Game_state game_state = Game_state::MAIN_MENU;

    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<GameRules> game_rules;
    std::unique_ptr<Player> player;
    std::unique_ptr<Settings> game_settings;
    std::unique_ptr<LevelStatsDisplay> level_stats_display;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Collectible>> collectibles;
    std::vector<std::unique_ptr<Area>> areas;

    void check_game_collisions();

};