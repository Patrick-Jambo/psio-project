#pragma once
#include <SFML/Graphics.hpp>

#include "core/ResourceManager.hpp"
#include "core/TileMap.hpp"
#include "core/SaveManager.hpp"
#include "core/SoundManager.hpp"

#include "ui/Button.hpp"
#include "ui/Settings.hpp"
#include "ui/MainMenu.hpp"
#include "ui/LevelStatsDisplay.hpp"
#include "ui/GameRules.hpp"
#include "ui/LevelTransition.hpp"
#include "ui/EndGameScreen.hpp"
#include "ui/LevelSelector.hpp"

#include "objects/Player.hpp"
#include "objects/Enemy.hpp"
#include "objects/Collectible.hpp"

#include "areas/Area.hpp"
#include <memory>

class Game {
public:
    Game();
    void run();
    Player& get_player() { return *player; }
    SoundManager& get_sound_manager() { return *sound_manager; }
    void advance_level();
    bool can_advance_level() const { return collected_count >= total_collectibles; }

private:
    void handle_events();
    void update(float dt);
    void render();
    void init_level(const int& level_num);
    void render_pause_screen();
    void reset_level();



    sf::Clock game_clock;
    ResourceManager resources;
    sf::RenderWindow game_window;
    sf::Music bg_music;

    sf::Cursor default_cursor;
    sf::Cursor hand_cursor;

    enum class Game_state {
        MAIN_MENU,
        RULES,
        TRANSITION,
        END_MENU,
        PLAYING,
        PAUSED
    };

    int current_level = 1;
    int death_counter = 0;
    float level_time = 0.0f;
    float total_game_time = 0.0f;
    int total_collectibles = 0;
    int collected_count = 0;

    bool is_settings_open = false;
    bool is_selector_open = false;
    bool is_selector_run = false;


    TileMap level_map;
    Game_state game_state = Game_state::MAIN_MENU;

    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<GameRules> game_rules;
    std::unique_ptr<Player> player;
    std::unique_ptr<Settings> game_settings;
    std::unique_ptr<LevelStatsDisplay> level_stats_display;
    std::unique_ptr<LevelTransition> level_transition;
    std::unique_ptr<EndGameScreen> end_game_screen;
    std::unique_ptr<SoundManager> sound_manager;
    std::unique_ptr<LevelSelector> level_selector;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Collectible>> collectibles;
    std::vector<std::unique_ptr<Area>> areas;

    void check_game_collisions();

};