#include "LevelManager.hpp"
#include "../areas/Area.hpp"
#include "../areas/CheckpointArea.hpp"
#include "../areas/GoalArea.hpp"

std::vector<std::vector<int>> LevelManager::get_level(const int& level_num) {
    switch (level_num) {
        case 1: return create_level_1();
        case 2: return create_level_2();
        case 3: return create_level_3();
        default: return {{}};
    }
}

sf::Vector2f LevelManager::get_player_start_pos(const int& level_num) {
    sf::Vector2f player_start_pos;
    switch (level_num) {
        case 1:
            player_start_pos.x = 150.0f;
            player_start_pos.y = 300.0f;
            break;
        case 2:
            player_start_pos.x = 64 * 2;
            player_start_pos.y = 64 * 6;
            break;

        default:
            player_start_pos.x = 100.0f;
            player_start_pos.y = 100.0f;
    }
    return player_start_pos;
}

std::vector<std::unique_ptr<Enemy>> LevelManager::get_level_enemies(const int &level_num, ResourceManager& resources) {
    std::vector<std::unique_ptr<Enemy>> level_enemies;

    switch (level_num) {
        case 1: {
            float e1_speed = 400.0f;

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(352.0f, 288.0f),
                sf::Vector2f(928.0f, 288.0f),
                e1_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(352.0f, 416.0f),
                sf::Vector2f(928.0f, 416.0f),
                e1_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(928.0f, 352.0f),
                sf::Vector2f(352.0f, 352.0f),
                e1_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(928.0f, 480.0f),
                sf::Vector2f(352.0f, 480.0f),
                e1_speed, resources
            ));
            break;
        }
        case 2: {
            constexpr float enemy_speed = 275.0f;
            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 4 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 4 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 5 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 5 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 6 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 6 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 7 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 7 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 8 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 8 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 9 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 9 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 10 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 10 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 11 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 11 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 12 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 12 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 13 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 13 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 14 + 32, 64 * 3 + 32),
                sf::Vector2f(64 * 14 + 32, 64 * 3 + 32 + 64 * 5),
                enemy_speed, resources
            ));

            level_enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(64 * 15 + 32, 64 * 3 + 32 + 64 * 5),
                sf::Vector2f(64 * 15 + 32, 64 * 3 + 32),
                enemy_speed, resources
            ));

            break;
        }

        default:
            break;
    }

    return level_enemies;
}

std::vector<std::unique_ptr<Collectible>> LevelManager::get_level_collectibles(const int &level_num, ResourceManager& resources) {
    std::vector<std::unique_ptr<Collectible>> level_collectibles;

    switch (level_num) {
        case 1:
            return {};
        case 2:
            level_collectibles.emplace_back(std::make_unique<Collectible>(sf::Vector2f(64 * 10, 64 * 6),resources));
        default:
            break;
    }

    return level_collectibles;
}

std::vector<std::vector<int>> LevelManager::create_level_1() {
    // --- ŚCIĄGAWKA DLA PROJEKTANTA ---
    // 3   - Grass (Trawa / Ściana)
    // 10  - Dirt środek | 20  - Dirt Dark środek | 30  - Area środek
    // 11x - Dirt krawędź| 21x - Dark krawędź     | 31x - Area krawędź
    // 12x - Dirt rog     | 22x - Dark róg         | 32x - Area róg
    // 13x - Dirt tunel   | 23x - Dark tunel       | 33x - Area tunel
    // Końcówki 'x' (rotacja): 0 = góra/TL, 1 = prawo/TR, 2 = dół/BR, 3 = lewo/BL

    std::vector<std::vector<int>> level_1 = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,320,310,321,3,3,3,3,3,3,3,3,3,3,220,131,310,310,321,3},
        {3,313,30,311,3,220,110,210,110,210,110,210,110,210,111,3,313,30,311,3},
        {3,313,30,311,3,113,20,10,20,10,20,10,20,10,211,3,313,30,311,3},
        {3,313,30,311,3,213,10,20,10,20,10,20,10,20,111,3,313,30,311,3},
        {3,313,30,311,3,113,212,112,212,112,212,112,212,112,222,3,313,30,311,3},
        {3,323,312,312,131,222,3,3,3,3,3,3,3,3,3,3,323,312,322,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };
    return level_1;
}

std::vector<std::vector<int>> LevelManager::create_level_2() {
    std::vector<std::vector<int>> level_2 = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,220,110,210,110,210,110,210,110,210,110,210,121,3,3,3,3},
        {3,3,3,3,113,20,10,20,10,20,10,20,10,20,10,211,3,3,3,3},
        {3,320,310,310,20,10,20,10,20,10,20,10,20,10,20,10,310,310,321,3},
        {3,323,312,312,10,20,10,20,10,20,10,20,10,20,10,20,312,312,322,3},
        {3,3,3,3,213,10,20,10,20,10,20,10,20,10,20,111,3,3,3,3},
        {3,3,3,3,123,212,112,212,112,212,112,212,112,212,112,222,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    };
    return level_2;
}

std::vector<std::vector<int> > LevelManager::create_level_3() {
    std::vector<std::vector<int>> level_3 = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,320,310,110,210,110,210,110,210,110,210,110,210,110,210,110,210,110,221,3},//początek ramka o 1 mniejsza od orginału
        {3,323,312,20,10,20,10,20,10,20,10,20,10,20,10,20,10,20,111,3},
        {3,3,3,113,20,10,20,10,20,10,20,10,20,10,20,10,20,10,211,3},
        {3,3,3,223,112,212,112,212,112,212,112,212,112,212,112,20,10,20,111,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,313,30,30,311,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,313,30,30,311,3},
        {3,3,3,120,210,110,210,110,210,110,210,110,210,110,210,10,20,10,211,3},
        {3,3,3,213,10,20,10,20,10,20,10,20,10,20,10,20,10,20,111,3},
        {3,320,310,10,20,10,20,10,20,10,20,10,20,10,20,10,20,10,211,3},
        {3,323,312,212,112,212,112,212,112,212,112,212,112,212,112,212,112,212,122,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };
    return level_3;
}

std::vector<std::unique_ptr<Area>> LevelManager::get_level_areas(const int& level_num) {
    std::vector<std::unique_ptr<Area>> level_areas;

    switch (level_num) {
        case 1:
            level_areas.emplace_back(std::make_unique<GoalArea>(sf::FloatRect(64*16,64*3,64*3,64*6)));
            break;

        case 2:
            level_areas.emplace_back(std::make_unique<GoalArea>(sf::FloatRect(64*16,64*5,64*3,64*2)));
            break;

        default:
            break;
    }

    return level_areas;
}