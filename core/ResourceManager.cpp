#include "ResourceManager.hpp"
#include <iostream>

const sf::Texture& ResourceManager::get_texture(const std::string &file_path) {
    auto it = textures.find(file_path);
    if (it != textures.end()) {
        return it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(file_path)) {
        std::cerr << "FAILED TO LOAD TEXTURE FROM PATH: " << file_path << std::endl;
    }

    textures[file_path] = texture;
    return textures[file_path];
}

const sf::Font& ResourceManager::get_font(const std::string& file_path) {
    auto it = fonts.find(file_path);
    if (it != fonts.end()) {
        return it->second;
    }

    sf::Font font;
    if (!font.loadFromFile(file_path)) {
        std::cerr << "FAILED TO LOAD FONT FROM PATH: " << file_path << std::endl;
    }

    fonts[file_path] = font;
    return fonts[file_path];
}

const sf::SoundBuffer& ResourceManager::get_sound_buffer(const std::string& file_path) {
    auto it = sound_buffers.find(file_path);
    if (it != sound_buffers.end()) {
        return it->second;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(file_path)) {
        std::cerr << "FAILED TO LOAD SOUND FROM PATH: " << file_path << std::endl;
    }

    sound_buffers[file_path] = buffer;
    return sound_buffers[file_path];
}
