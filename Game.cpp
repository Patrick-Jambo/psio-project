#include "Game.hpp"
#include "ui/Button.hpp"
#include "core/Config.hpp"
#include "core/LevelManager.hpp"
#include <iostream>


Game::Game() : level_map(resources) {
    game_window.create(
        sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT),
        Config::GAME_NAME,
        sf::Style::Titlebar | sf::Style::Close
    );
    game_window.setFramerateLimit(Config::GAME_FRAME_RATE);

    main_menu = std::make_unique<MainMenu>(resources);

    if (bg_music.openFromFile("assets/music/game_loop.mp3")) {
        bg_music.setLoop(true);
        bg_music.play();
    }

    if (default_cursor.loadFromSystem(sf::Cursor::Arrow)) {
        game_window.setMouseCursor(default_cursor);
    }
    hand_cursor.loadFromSystem(sf::Cursor::Hand);

    const sf::Font& font = resources.get_font("assets/fonts/Pixelmax-Regular.otf");
    game_settings = std::make_unique<Settings>(font, bg_music);
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
            game_window.close();
        }

        if (game_settings) {
            game_settings->handle_event(mouse_pos, event);
        }

        if (game_state == Game_state::MAIN_MENU) {
            bool start_game = false;
            main_menu->handle_event(mouse_pos, event, start_game);

            if (start_game) {
                game_window.setMouseCursor(default_cursor);
                init_level(current_level);
                game_state = Game_state::PLAYING;
            }
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
        player->update(dt, level_map);
        for (auto& enemy : enemies) enemy->update(dt, level_map);
        for (auto& collectible : collectibles) collectible->update(dt, level_map);
        check_game_collisions();
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

void Game::render() {
    game_window.clear(sf::Color(177, 179, 249));

    if (game_state == Game_state::MAIN_MENU) {
        main_menu->draw(game_window);
    }

    if (game_state == Game_state::PLAYING) {
        game_window.draw(level_map);

        for (auto& collectible : collectibles) {
            game_window.draw(*collectible);
        }

        for (auto& enemy : enemies) {
            game_window.draw(*enemy);
        }

        game_window.draw(*player);

        if (game_settings) {
            game_settings->draw(game_window);
        }

        for (auto& area : areas) {
            game_window.draw(*area);
        }
    }

    game_window.display();
}

void Game::init_level(const int& level_num) {
    // level tiles
    std::vector<std::vector<int>> first_level = LevelManager::get_level(level_num);
    level_map.load_level(first_level);

    // player spawn
    sf::Vector2f start_pos = LevelManager::get_player_start_pos(level_num);
    player = std::make_unique<Player>(start_pos, resources);

    // enemies and leaves
    enemies = LevelManager::get_level_enemies(level_num, resources);
    collectibles = LevelManager::get_level_collectibles(level_num, resources);

    areas = LevelManager::get_level_areas(level_num);
}

void Game::check_game_collisions() {
    sf::FloatRect player_hitbox = player->get_hitbox();

    if (game_settings && !game_settings->is_god_mode()) {
        for (auto& enemy : enemies) {
            if (player_hitbox.intersects(enemy->get_hitbox())) {
                player->setPosition(LevelManager::get_player_start_pos(current_level));
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
    current_level++;

    std::vector<std::vector<int>> next_level_tiles = LevelManager::get_level(current_level);

    if (next_level_tiles.empty()) {
        game_state = Game_state::MAIN_MENU;
        current_level = 1;
    } else {
        std::cout << "LOADING LEVEL: " << current_level << std::endl;
        init_level(current_level);
    }
}