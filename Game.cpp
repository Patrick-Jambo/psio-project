#include "Game.hpp"
#include "ui/Button.hpp"

Game::Game() {
    game_window.create(sf::VideoMode(game_window_width, game_window_height), GAME_NAME);
    game_window.setFramerateLimit(GAME_FRAME_RATE);

    const sf::Font& main_font = resources.get_font("assets/fonts/Pixelmax-Regular.otf");
    game_title.setFont(main_font);
    game_title.setString(GAME_NAME);
    game_title.setCharacterSize(70);
    game_title.setFillColor(sf::Color(255, 100, 0));
    game_title.setPosition(200, 150);

    play_button = std::make_unique<Button>(sf::Vector2f(500, 300), 100, "PLAY", main_font);

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
            if (play_button->clicked(mouse_pos, event)) {
                game_state = Game_state::PLAYING;
            }
        }


    }
}

void Game::update(float dt) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(game_window);
    if (game_state == Game_state::MAIN_MENU) {
        play_button->update(mouse_pos);
    }

    if (play_button->mouse_hover(mouse_pos)) {
        game_window.setMouseCursor(hand_cursor);
    } else {
        game_window.setMouseCursor(default_cursor);
    }

    if (game_state == Game_state::PLAYING) {
        // stub
    }
}

void Game::render() {
    game_window.clear(sf::Color(177, 179, 249));

    if (game_state == Game_state::MAIN_MENU) {
        game_window.draw(game_title);
        play_button->draw(game_window);
    }

    if (game_state == Game_state::PLAYING) {
        // stub
    }

    game_window.display();
}
