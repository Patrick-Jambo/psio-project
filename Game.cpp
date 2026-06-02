#include "Game.hpp"

Game::Game() {
    game_window.create(sf::VideoMode(game_window_width, game_window_height), "WHG");
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
    while (game_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game_window.close();
        }
    }
}

void Game::update(float dt) {
    if (game_state_ == Game_state::PLAYING) {
        // stub
    }
}

void Game::render() {
    game_window.clear();

    if (game_state_ == Game_state::PLAYING) {
        // stub
    }

    game_window.display();
}
