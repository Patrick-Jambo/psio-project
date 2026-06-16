#include "LevelSelector.hpp"
#include "../core/Config.hpp"

LevelSelector::LevelSelector(ResourceManager& resources) {
    const sf::Font& font = resources.get_font("assets/fonts/Pixeled.ttf");
    int char_size = 18;

    float win_width = 800.0f;
    float win_height = 450.0f;
    float win_x = (Config::WINDOW_WIDTH - win_width) / 2.0f;
    float win_y = (Config::WINDOW_HEIGHT - win_height) / 2.0f;

    window_background.setPosition(win_x, win_y);
    window_background.setSize(sf::Vector2f(win_width, win_height));
    window_background.setFillColor(sf::Color(30, 30, 45, 245));
    window_background.setOutlineColor(sf::Color::Black);
    window_background.setOutlineThickness(4.0f);

    window_title.setFont(font);
    window_title.setString("SELECT LEVEL");
    window_title.setCharacterSize(28);
    window_title.setFillColor(sf::Color(255, 100, 0));
    window_title.setOutlineColor(sf::Color::Black);
    window_title.setOutlineThickness(3.0f);
    window_title.setPosition(win_x + (win_width - window_title.getGlobalBounds().width) / 2.0f, win_y + 20.0f);

    close_button = std::make_unique<Button>(sf::Vector2f(win_x + win_width - 45.0f, win_y + 15.0f), 22, "X", font);
    close_button->set_text_colors(sf::Color::White, sf::Color::Red);
    close_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    float start_grid_x = win_x + 50.0f;
    float start_grid_y = win_y + 130.0f;
    float spacing_x = 140.0f;
    float spacing_y = 120.0f;

    for (int i = 0; i < 10; ++i) {
        int row = i / 5;
        int col = i % 5;

        float btn_x = start_grid_x + (col * spacing_x);
        float btn_y = start_grid_y + (row * spacing_y);

        std::string lv_text = "LV " + std::to_string(i + 1);
        auto btn = std::make_unique<Button>(sf::Vector2f(btn_x, btn_y), char_size, lv_text, font);
        btn->set_text_colors(sf::Color::White, sf::Color(255, 152, 2));
        btn->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

        level_buttons.push_back(std::move(btn));
    }
}

void LevelSelector::handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& should_close, int& selected_level) {
    if (close_button->clicked(mouse_pos, event)) {
        should_close = true;
    }

    for (int i = 0; i < 10; ++i) {
        if (level_buttons[i]->clicked(mouse_pos, event)) {
            selected_level = i + 1;
        }
    }
}

void LevelSelector::update(const sf::Vector2i& mouse_pos) {
    close_button->update(mouse_pos);
    for (auto& btn : level_buttons) {
        btn->update(mouse_pos);
    }
}

void LevelSelector::draw(sf::RenderWindow& window) {
    window.draw(window_background);
    window.draw(window_title);
    close_button->draw(window);
    for (auto& btn : level_buttons) {
        btn->draw(window);
    }
}

bool LevelSelector::any_button_hovered() const {
    if (close_button && close_button->is_mouse_over()) return true;
    for (auto& btn : level_buttons) {
        if (btn && btn->is_mouse_over()) return true;
    }
    return false;
}