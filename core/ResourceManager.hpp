#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceManager {
public:
    ResourceManager() = default;
    const sf::Texture& get_texture(const std::string& file_path);
    const sf::Font& get_font(const std::string& file_path);
    const sf::SoundBuffer& get_sound_buffer(const std::string& file_path);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> sound_buffers;

};
