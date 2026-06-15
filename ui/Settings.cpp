#include "Settings.hpp"
#include "../core/Config.hpp"
#include "../core/Utils.hpp"

bool Settings::music_enabled = true;
bool Settings::sounds_enabled = true;
bool Settings::god_mode_enabled = false;
bool Settings::hitboxes_enabled = false;
float Settings::volume = 70.0f;

Settings::Settings(const sf::Font& font, sf::Music& bg_music) : music_ref(bg_music) {
    int char_size = 18;
    float win_width = 600.0f;
    float win_height = 500.0f;
    float win_x = (Config::WINDOW_WIDTH - win_width) / 2.0f;
    float win_y = (Config::WINDOW_HEIGHT - win_height) / 2.0f;

    window_background.setPosition(win_x, win_y);
    window_background.setSize(sf::Vector2f(win_width, win_height));
    window_background.setFillColor(sf::Color(30, 30, 45, 245));
    window_background.setOutlineColor(sf::Color::Black);
    window_background.setOutlineThickness(4.0f);

    window_title.setFont(font);
    window_title.setString("SETTINGS");
    window_title.setCharacterSize(28);
    window_title.setFillColor(sf::Color(255, 100, 0));
    window_title.setOutlineColor(sf::Color::Black);
    window_title.setOutlineThickness(3.0f);
    window_title.setPosition(win_x + (win_width - window_title.getGlobalBounds().width) / 2.0f, win_y + 20.0f);

    close_button = std::make_unique<Button>(sf::Vector2f(win_x + win_width - 45.0f, win_y + 15.0f), 22, "X", font);
    close_button->set_text_colors(sf::Color::White, sf::Color::Red);
    close_button->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);

    float start_button_y = win_y + 90.0f;
    float button_spacing = 58.0f;

    std::string music_txt = Settings::music_enabled ? "MUSIC: ON" : "MUSIC: OFF";
    std::string sound_txt = Settings::sounds_enabled ? "SOUNDS: ON" : "SOUNDS: OFF";
    std::string god_txt = Settings::god_mode_enabled ? "GOD MODE: ON" : "GOD MODE: OFF";
    std::string hit_txt = Settings::hitboxes_enabled ? "HITBOXES: ON" : "HITBOXES: OFF";

    music_button = std::make_unique<Button>(sf::Vector2f(0, start_button_y), char_size, music_txt, font);
    music_button->set_position(sf::Vector2f(win_x + (win_width - music_button->get_width()) / 2.0f, start_button_y));

    start_button_y += button_spacing;
    sounds_button = std::make_unique<Button>(sf::Vector2f(0, start_button_y), char_size, sound_txt, font);
    sounds_button->set_position(sf::Vector2f(win_x + (win_width - sounds_button->get_width()) / 2.0f, start_button_y));

    start_button_y += button_spacing;
    god_mode_button = std::make_unique<Button>(sf::Vector2f(0, start_button_y), char_size, god_txt, font);
    god_mode_button->set_position(sf::Vector2f(win_x + (win_width - god_mode_button->get_width()) / 2.0f, start_button_y));

    start_button_y += button_spacing;
    hitboxes_button = std::make_unique<Button>(sf::Vector2f(0, start_button_y), char_size, hit_txt, font);
    hitboxes_button->set_position(sf::Vector2f(win_x + (win_width - hitboxes_button->get_width()) / 2.0f, start_button_y));

    start_button_y += button_spacing + 10.0f;

    vol_display_text.setFont(font);
    vol_display_text.setCharacterSize(char_size);
    vol_display_text.setFillColor(sf::Color::White);
    vol_display_text.setOutlineColor(sf::Color::Black);
    vol_display_text.setOutlineThickness(2.0f);

    vol_minus_btn = std::make_unique<Button>(sf::Vector2f(0.0f, start_button_y), char_size, "[-]", font);
    vol_plus_btn = std::make_unique<Button>(sf::Vector2f(0.0f, start_button_y), char_size, "[+]", font);

    update_volume_text(start_button_y);

    auto setup_btn_visuals = [](std::unique_ptr<Button>& btn) {
        btn->set_text_colors(sf::Color::White, sf::Color(255, 152, 2));
        btn->set_text_outlines(sf::Color::Black, sf::Color::Black, 2.0f);
    };
    setup_btn_visuals(music_button);
    setup_btn_visuals(sounds_button);
    setup_btn_visuals(god_mode_button);
    setup_btn_visuals(hitboxes_button);
    setup_btn_visuals(vol_minus_btn);
    setup_btn_visuals(vol_plus_btn);

    if (!Settings::music_enabled) music_button->set_text_colors(sf::Color::White, sf::Color::Red);
    if (!Settings::sounds_enabled) sounds_button->set_text_colors(sf::Color::White, sf::Color::Red);
}

void Settings::handle_event(const sf::Vector2i& mouse_pos, const sf::Event& event, bool& should_close) {
    if (close_button->clicked(mouse_pos, event)) should_close = true;

    if (music_button->clicked(mouse_pos, event)) {
        music_enabled = !music_enabled;
        if (music_enabled) {
            music_ref.setVolume(volume); // Przywracamy poziom dźwięku muzyki
            music_ref.play();
            music_button->set_text_string("MUSIC: ON");
            music_button->set_text_colors(sf::Color::White, sf::Color(255, 152, 2));
        } else {
            music_ref.pause();
            music_button->set_text_string("MUSIC: OFF");
            music_button->set_text_colors(sf::Color::White, sf::Color::Red);
        }
    }

    if (sounds_button->clicked(mouse_pos, event)) {
        sounds_enabled = !sounds_enabled;
        if (sounds_enabled) {
            sounds_button->set_text_string("SOUNDS: ON");
            sounds_button->set_text_colors(sf::Color::White, sf::Color(255, 152, 2));
        } else {
            sounds_button->set_text_string("SOUNDS: OFF");
            sounds_button->set_text_colors(sf::Color::White, sf::Color::Red);
        }
    }

    if (god_mode_button->clicked(mouse_pos, event)) {
        god_mode_enabled = !god_mode_enabled;
        god_mode_button->set_text_string(god_mode_enabled ? "GOD MODE: ON" : "GOD MODE: OFF");
    }

    if (hitboxes_button->clicked(mouse_pos, event)) {
        hitboxes_enabled = !hitboxes_enabled;
        hitboxes_button->set_text_string(hitboxes_enabled ? "HITBOXES: ON" : "HITBOXES: OFF");
    }

    if (vol_minus_btn->clicked(mouse_pos, event)) {
        volume -= 10.0f;
        if (volume < 0.0f) volume = 0.0f;

        music_ref.setVolume(volume);
        update_volume_text(vol_display_text.getPosition().y);
    }

    if (vol_plus_btn->clicked(mouse_pos, event)) {
        volume += 10.0f;
        if (volume > 100.0f) volume = 100.0f;

        if (music_enabled) music_ref.setVolume(volume);
        update_volume_text(vol_display_text.getPosition().y);
    }
}

void Settings::update(const sf::Vector2i& mouse_pos) {
    close_button->update(mouse_pos);
    music_button->update(mouse_pos);
    sounds_button->update(mouse_pos);
    god_mode_button->update(mouse_pos);
    hitboxes_button->update(mouse_pos);
    vol_minus_btn->update(mouse_pos);
    vol_plus_btn->update(mouse_pos);
}

void Settings::draw(sf::RenderWindow& window) {
    window.draw(window_background);
    window.draw(window_title);
    close_button->draw(window);
    music_button->draw(window);
    sounds_button->draw(window);
    god_mode_button->draw(window);
    hitboxes_button->draw(window);

    window.draw(vol_display_text);
    vol_minus_btn->draw(window);
    vol_plus_btn->draw(window);
}

bool Settings::any_button_hovered() const {
    return (close_button && close_button->is_mouse_over()) ||
           (music_button && music_button->is_mouse_over()) ||
           (sounds_button && sounds_button->is_mouse_over()) ||
           (god_mode_button && god_mode_button->is_mouse_over()) ||
           (hitboxes_button && hitboxes_button->is_mouse_over()) ||
           (vol_minus_btn && vol_minus_btn->is_mouse_over()) ||
           (vol_plus_btn && vol_plus_btn->is_mouse_over());
}

void Settings::update_volume_text(float current_y) {
    int bars = static_cast<int>(volume) / 10;
    std::string bar_str = "VOLUME: [";
    for (int i = 0; i < 10; i++) {
        if (i < bars) bar_str += "|";
        else bar_str += ".";
    }
    bar_str += "]";
    vol_display_text.setString(bar_str);

    float win_width = 600.0f;
    float win_x = (Config::WINDOW_WIDTH - win_width) / 2.0f;

    float text_x = win_x + (win_width - vol_display_text.getGlobalBounds().width) / 2.0f;
    vol_display_text.setPosition(text_x, current_y);

    if (vol_minus_btn && vol_plus_btn) {
        float minus_x = vol_display_text.getPosition().x - 50.0f;
        vol_minus_btn->set_position(sf::Vector2f(minus_x, current_y));

        float plus_x = vol_display_text.getPosition().x + vol_display_text.getGlobalBounds().width + 20.0f;
        vol_plus_btn->set_position(sf::Vector2f(plus_x, current_y));
    }
}