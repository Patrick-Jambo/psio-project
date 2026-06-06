#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "ResourceManager.hpp"

class TileMap : public sf::Drawable {
public:
    TileMap(ResourceManager& resources);

    void load_level(const std::vector<std::vector<int>>& level_data);
    bool check_wall_collision(const sf::FloatRect& future_hitbox) const;
    int get_tile_type_at_pos(sf::Vector2f pos) const;

private:
    int tile_size = 64;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<std::vector<int>> map_grid;
    std::map<int, sf::Texture> textures;
};