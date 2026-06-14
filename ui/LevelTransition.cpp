#include "../ui/LevelTransition.hpp"
#include "../core/Config.hpp"

LevelTransition::LevelTransition(ResourceManager& resources) {
    display_text.setFont(resources.get_font("assets/fonts/Pixeled.ttf"));
    display_text.setCharacterSize(32);
    display_text.setFillColor(sf::Color::White);

    background.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    background.setFillColor(sf::Color(20, 20, 20, 255));
}

void LevelTransition::start(const std::string& text) {
    display_text.setString(text);

    sf::FloatRect text_rect = display_text.getLocalBounds();
    display_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                           text_rect.top  + text_rect.height / 2.0f);
    display_text.setPosition(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f);

    timer = 0.0f;
}

bool LevelTransition::update(float dt) {
    timer += dt;
    return timer >= DURATION;
}

void LevelTransition::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(display_text);
}