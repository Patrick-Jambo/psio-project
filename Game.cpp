#include "Game.hpp"

Game::Game() {
    const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    game_window.create(desktop, "WHG", sf::Style::Fullscreen);
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
