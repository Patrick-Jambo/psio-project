#include "SoundManager.hpp"
#include "../ui/Settings.hpp"
#include <cstdlib> // rand()

SoundManager::SoundManager(ResourceManager& res) : resources(res) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::string SoundManager::get_random_sound(const std::string &sound_prefix, const int& sounds_num) {
    int random_index = std::rand() % sounds_num;
    return "assets/sounds/" + sound_prefix + std::to_string(random_index) + ".ogg";
}

void SoundManager::play_sound(const std::string& file_path) {
    if (!Settings::sounds_enabled) return;

    const sf::SoundBuffer& buffer = resources.get_sound_buffer(file_path);
    active_sounds.emplace_back();
    sf::Sound& sound = active_sounds.back();
    sound.setBuffer(buffer);

    sound.setVolume(Settings::volume);
    sound.play();
}

void SoundManager::play_death_sound() {
    play_sound(get_random_sound("death_", 4));
}

void SoundManager::play_collect_sound() {
    play_sound(get_random_sound("collect_", 2));
}

void SoundManager::play_level_clear_sound() {
    play_sound(get_random_sound("level_clear_", 2));
}

void SoundManager::play_checkpoint_sound() {
    play_sound(get_random_sound("checkpoint_", 2));
}

void SoundManager::update() {
    // free memory
    active_sounds.erase(
        std::remove_if(active_sounds.begin(), active_sounds.end(),
            [](const sf::Sound& sound) {
                return sound.getStatus() == sf::Sound::Stopped;
            }),
        active_sounds.end()
    );
}