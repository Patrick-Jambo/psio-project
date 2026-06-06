#include "TileMap.hpp"

TileMap::TileMap(ResourceManager &resources) {
    textures[10] = resources.get_texture("assets/img/dirt.png");
    textures[20] = resources.get_texture("assets/img/dirt_dark.png");
    textures[30] = resources.get_texture("assets/img/area.png");
    textures[3]  = resources.get_texture("assets/img/grass.png");

    textures[11] = resources.get_texture("assets/img/dirt_side.png");
    textures[21] = resources.get_texture("assets/img/dirt_side_dark.png");
    textures[31] = resources.get_texture("assets/img/area_side.png");

    textures[12] = resources.get_texture("assets/img/dirt_corner.png");
    textures[22] = resources.get_texture("assets/img/dirt_corner_dark.png");
    textures[32] = resources.get_texture("assets/img/area_corner.png");

    textures[13] = resources.get_texture("assets/img/dirt_double_side.png");
    textures[23] = resources.get_texture("assets/img/dirt_double_side_dark.png");
    textures[33] = resources.get_texture("assets/img/area_double_side.png");
}

void TileMap::load_level(const std::vector<std::vector<int>>& level_data) {
    map_grid = level_data;
}

bool TileMap::check_wall_collision(const sf::FloatRect& future_hitbox) const {
    int start_x = static_cast<int>(future_hitbox.left) / tile_size;
    int end_x   = static_cast<int>(future_hitbox.left + future_hitbox.width) / tile_size;
    int start_y = static_cast<int>(future_hitbox.top) / tile_size;
    int end_y   = static_cast<int>(future_hitbox.top + future_hitbox.height) / tile_size;

    if (start_x < 0 || end_x >= map_grid[0].size() || start_y < 0 || end_y >= map_grid.size()) {
        return true;
    }

    for (int y = start_y; y <= end_y; y++) {
        for (int x = start_x; x <= end_x; x++) {
            if (map_grid[y][x] == 3) {
                return true; // Trawa to ściana
            }
        }
    }
    return false;
}

int TileMap::get_tile_type_at_pos(sf::Vector2f pos) const {
    int x = static_cast<int>(pos.x) / tile_size;
    int y = static_cast<int>(pos.y) / tile_size;

    if (y >= 0 && y < map_grid.size() && x >= 0 && x < map_grid[y].size()) {
        int tile_id = map_grid[y][x];
        if (tile_id == 3) return 3;

        if (tile_id >= 100) return (tile_id / 100) * 10;
        return (tile_id / 10) * 10;
    }
    return 3;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;

    for (size_t y = 0; y < map_grid.size(); y++) {
        for (size_t x = 0; x < map_grid[y].size(); x++) {
            int tile_id = map_grid[y][x];

            int texture_key = tile_id;
            float rotation = 0.0f;

            // ( 320, 220, 131)
            if (tile_id >= 100) {
                int rotation_index = tile_id % 10;
                rotation = rotation_index * 90.0f;
                texture_key = tile_id / 10; // Zostają dziesiątki (np. 320 / 10 = 32)
            }
            // (11, 23, 31 - końcówki inne niż 0)
            else if (tile_id >= 10 && (tile_id % 10 != 0)) {
                int rotation_index = tile_id % 10;
                rotation = rotation_index * 90.0f;
                texture_key = tile_id / 10;
            }
            // 3. Dla 10, 20, 30 oraz 3: texture_key pozostaje równy tile_id, rotacja = 0.0f

            if (textures.find(texture_key) != textures.end()) {
                sprite.setTexture(textures.at(texture_key), true);
                sprite.setOrigin(tile_size / 2.0f, tile_size / 2.0f);

                float pos_x = x * tile_size + (tile_size / 2.0f);
                float pos_y = y * tile_size + (tile_size / 2.0f);

                sprite.setPosition(pos_x, pos_y);
                sprite.setRotation(rotation);
                target.draw(sprite, states);
            }
        }
    }
}