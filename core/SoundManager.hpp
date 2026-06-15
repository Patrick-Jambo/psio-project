#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "ResourceManager.hpp"

class SoundManager {
public:
    SoundManager(ResourceManager& res);
    void play_death_sound();
    void play_collect_sound();
    void play_level_clear_sound();
    void play_checkpoint_sound();

    static std::string get_random_sound(const std::string& sound_prefix, const int& sounds_num);


    void update();

private:
    ResourceManager& resources;
    std::vector<sf::Sound> active_sounds;

    // Uniwersalna metoda pomocnicza do odpalenia konkretnego pliku
    void play_sound(const std::string& file_path);
};