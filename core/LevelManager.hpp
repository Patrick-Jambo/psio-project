#pragma once
#include "../objects/Enemy.hpp"
#include "../objects/Collectible.hpp"
#include "../core/ResourceManager.hpp"
#include "../areas/Area.hpp"
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class LevelManager {
public:
    static sf::Vector2f get_player_start_pos(const int& level_num);
    static std::vector<std::vector<int>> get_level(const int& level_num);
    static std::vector<std::unique_ptr<Area>> get_level_areas(const int& level_num, ResourceManager& resources);
    static std::vector<std::unique_ptr<Enemy>> get_level_enemies(const int &level_num, ResourceManager& resources);
    static std::vector<std::unique_ptr<Collectible>> get_level_collectibles(const int &level_num, ResourceManager& resources);
private:
    static std::vector<std::vector<int>> create_level_1();
    static std::vector<std::vector<int>> create_level_2();
    static std::vector<std::vector<int>> create_level_3();
    static std::vector<std::vector<int>> create_level_4();
    static std::vector<std::vector<int>> create_level_5();
    static std::vector<std::vector<int>> create_level_6();
    static std::vector<std::vector<int>> create_level_7();
    static std::vector<std::vector<int>> create_level_8();
    static std::vector<std::vector<int>> create_level_9();
    static std::vector<std::vector<int>> create_level_10();
};