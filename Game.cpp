#include "Game.hpp"
#include "ui/Button.hpp"
#include "core/Config.hpp"

Game::Game() {
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

        if (game_state == Game_state::MAIN_MENU) {
            bool start_game = false;
            main_menu->handle_event(mouse_pos, event, start_game);

            if (start_game) {
                game_window.setMouseCursor(default_cursor);
                game_state = Game_state::PLAYING;
                player = std::make_unique<Player>(sf::Vector2f(100, 100), resources);
            }
        }
    }
}

void Game::update(float dt) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(game_window);

    if (game_state == Game_state::MAIN_MENU) {
        main_menu->update(mouse_pos);

        if (main_menu->play_button_hover(mouse_pos)) {
            game_window.setMouseCursor(hand_cursor);
        } else {
            game_window.setMouseCursor(default_cursor);
        }
    }

    if (game_state == Game_state::PLAYING) {
        player->update(dt);
    }
}

void Game::render() {
    game_window.clear(sf::Color(177, 179, 249));

    if (game_state == Game_state::MAIN_MENU) {
        main_menu->draw(game_window);
    }

    if (game_state == Game_state::PLAYING) {
        game_window.draw(*player);
    }

    game_window.display();
}