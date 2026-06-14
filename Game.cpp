#include "Game.hpp"
#include "ui/Button.hpp"
#include "core/Config.hpp"
#include "core/LevelManager.hpp"
#include "ui/LevelStatsDisplay.hpp"
#include "areas/CheckpointArea.hpp"
#include "core/Utils.hpp"
#include <iostream>


Game::Game() : level_map(resources) {
    game_window.create(
        sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT),
        Config::GAME_NAME,
        sf::Style::Titlebar | sf::Style::Close
    );

    SaveManager::load("assets/data/levels_data.json");

    game_window.setFramerateLimit(Config::GAME_FRAME_RATE);

    main_menu = std::make_unique<MainMenu>(resources);

    if (bg_music.openFromFile("assets/music/game_loop.mp3")) {
        bg_music.setLoop(true);
        if (Settings::music_enabled) {
            bg_music.play();
        }
    }

    if (default_cursor.loadFromSystem(sf::Cursor::Arrow)) {
        game_window.setMouseCursor(default_cursor);
    }
    hand_cursor.loadFromSystem(sf::Cursor::Hand);

    const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
    game_settings = std::make_unique<Settings>(font, bg_music);

    level_stats_display = std::make_unique<LevelStatsDisplay>(resources);
    game_rules = std::make_unique<GameRules>(resources);
    level_transition = std::make_unique<LevelTransition>(resources);
    end_game_screen = std::make_unique<EndGameScreen>(resources);

}

void Game::run() {
    while (game_window.isOpen()) {
        float dt = game_clock.restart().asSeconds();
        handle_events();
        update(dt);
        render();
    }
}

void Game::handle_events() {
    sf::Event event;
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(game_window);

    while (game_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            SaveManager::save_settings();
            SaveManager::save();
            game_window.close();
        }

        if (game_settings) {
            game_settings->handle_event(mouse_pos, event);
        }

        switch (game_state) {
            case Game_state::MAIN_MENU: {
                bool start_game = false;
                main_menu->handle_event(mouse_pos, event, start_game);

                if (start_game) {
                    game_state = Game_state::RULES;
                }
                break;
            }

            case Game_state::RULES: {
                bool return_to_main_menu = false;
                bool start_playing = false;

                if (game_rules) {
                    game_rules->handle_event(event, start_playing, return_to_main_menu);
                }

                if (start_playing) {
                    game_window.setMouseCursor(default_cursor);

                    std::string text_from_json = SaveManager::get_intertitle(current_level);
                    level_transition->start(text_from_json);

                    game_state = Game_state::TRANSITION;
                }

                else if (return_to_main_menu) {
                    game_state = Game_state::MAIN_MENU;
                }
                break;
            }

            case Game_state::PLAYING: {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    game_state = Game_state::PAUSED;
                }
                break;
            }

            case Game_state::PAUSED: {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    game_state = Game_state::PLAYING;
                }
                break;
            }

            case Game_state::END_MENU: {
                bool return_to_menu = false;
                if (end_game_screen) {
                    end_game_screen->handle_event(event, return_to_menu);
                }

                if (return_to_menu) {
                    // full game reset
                    current_level = 1;
                    death_counter = 0;
                    total_game_time = 0.0f;
                    game_state = Game_state::MAIN_MENU;
                }
                break;
            }

            default:
                break;
        }
    }
}

void Game::update(float dt) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(game_window);

    if (game_settings) {
        game_settings->update(mouse_pos);
    }

    if (game_state == Game_state::MAIN_MENU) {
        main_menu->update(mouse_pos);
    }

    if (game_state == Game_state::PLAYING) {
        level_time+=dt;
        total_game_time+=dt;
        player->update(dt, level_map);

        for (auto& enemy : enemies) enemy->update(dt, level_map);

        for (auto& collectible : collectibles) collectible->update(dt, level_map);

        for (auto& area : areas) {
            // Próbujemy rzutować Area na CheckpointArea
            auto* checkpoint = dynamic_cast<CheckpointArea*>(area.get());
            if (checkpoint) {
                checkpoint->update(dt);
            }
        }

        check_game_collisions();

        if (level_stats_display) {
            level_stats_display->update(level_time, death_counter);
        }
    }

    if (game_state == Game_state::TRANSITION) {
        if (level_transition->update(dt)) {
            init_level(current_level);
            game_state = Game_state::PLAYING;
        }
    }

    bool need_hand_cursor = false;

    if (game_settings && game_settings->any_button_hovered()) {
        need_hand_cursor = true;
    }

    else if (game_state == Game_state::MAIN_MENU && main_menu->get_play_button().is_mouse_over()) {
        need_hand_cursor = true;
    }

    if (need_hand_cursor) {
        game_window.setMouseCursor(hand_cursor);
    } else {
        game_window.setMouseCursor(default_cursor);
    }
}

void Game::render_pause_screen() {
    sf::RectangleShape pause_overlay(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    pause_overlay.setFillColor(sf::Color(0, 0, 0, 150));
    game_window.draw(pause_overlay);

    const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
    sf::Text pause_text;
    pause_text.setFont(font);
    pause_text.setString("PAUSED");
    pause_text.setCharacterSize(70);
    pause_text.setFillColor(sf::Color::White);
    pause_text.setOutlineColor(sf::Color::Black);
    pause_text.setOutlineThickness(4.0f);

    float text_x = Utils::get_centered_x(pause_text.getGlobalBounds().width);
    float text_y = (Config::WINDOW_HEIGHT / 2.0f) - (pause_text.getGlobalBounds().height / 2.0f);
    pause_text.setPosition(text_x, text_y);

    game_window.draw(pause_text);
}

void Game::render() {
    game_window.clear(sf::Color(177, 179, 249));

    if (game_state == Game_state::MAIN_MENU)  main_menu->draw(game_window);
    if (game_state == Game_state::RULES)      game_rules->draw(game_window);
    if (game_state == Game_state::TRANSITION) level_transition->draw(game_window);

    if (game_state == Game_state::PLAYING || game_state == Game_state::PAUSED) {
        game_window.draw(level_map);

        for (auto& area : areas) game_window.draw(*area);
        for (auto& collectible : collectibles) game_window.draw(*collectible);
        for (auto& enemy : enemies) game_window.draw(*enemy);
        game_window.draw(*player);

        if (game_settings) game_settings->draw(game_window);
        if (level_stats_display) level_stats_display->draw(game_window);

        if (game_state == Game_state::PAUSED) {
            render_pause_screen();
        }
    }

    if (game_state == Game_state::END_MENU) {
        if (end_game_screen) end_game_screen->draw(game_window);
    }

    game_window.display();
}

void Game::init_level(const int& level_num) {
    // loads levels
    level_time = 0.0f;

    std::vector<std::vector<int>> level_tiles = LevelManager::get_level(level_num);
    level_map.load_level(level_tiles);


    // player spawn
    sf::Vector2f start_pos = LevelManager::get_player_start_pos(level_num);
    std::cout << "X: " << start_pos.x << " Y: " << start_pos.y << std::endl;
    player = std::make_unique<Player>(start_pos, resources);

    // enemies and leaves
    enemies = LevelManager::get_level_enemies(level_num, resources);
    collectibles = LevelManager::get_level_collectibles(level_num, resources);

    areas = LevelManager::get_level_areas(level_num,resources);
}

void Game::check_game_collisions() {
    sf::FloatRect player_hitbox = player->get_hitbox();

    if (game_settings && !game_settings->is_god_mode()) {
        for (auto& enemy : enemies) {
            if (player_hitbox.intersects(enemy->get_hitbox())) {
                death_counter++;
                //TODO: ADD DEATH ANIMATION
                player->respawn();
                return;
            }
        }
    }

    for (auto& collectible : collectibles) {
        if (player_hitbox.intersects(collectible->get_hitbox()) && !collectible->is_collected()) {
            collectible->collect();
        }
    }

    for (auto& area : areas) {
        if (player_hitbox.intersects(area->get_bounds())) {
            area->on_enter(*this);
        }
    }
}

void Game::advance_level() {
    SaveManager::update_best_time(current_level,level_time);
    current_level++;

    std::vector<std::vector<int>> next_level_tiles = LevelManager::get_level(current_level);

    if (next_level_tiles.empty()) {
        std::cout << "GAME COMPLETED! CHANGING TO END GAME SCREEN..." << std::endl;

        bool is_new_death_record = false;
        bool is_new_time_record = false;

        SaveManager::update_global_records(death_counter, total_game_time, is_new_death_record, is_new_time_record);

        int best_deaths = SaveManager::get_global_death_record();
        float best_time = SaveManager::get_global_time_record();

        const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
        if (end_game_screen) {
            end_game_screen->setup_final_scores(
                font,
                death_counter,
                total_game_time,
                is_new_death_record,
                is_new_time_record,
                best_deaths,
                best_time
            );
        }
        game_state = Game_state::END_MENU;
    } else {
        std::cout << "PREPARING LEVEL: " << current_level << std::endl;
        std::string text_from_json = SaveManager::get_intertitle(current_level);
        level_transition->start(text_from_json);

        game_state = Game_state::TRANSITION;
    }
}