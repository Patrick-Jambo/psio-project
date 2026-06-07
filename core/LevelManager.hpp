#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class LevelManager {
public:
    static std::vector<std::vector<int>> get_level(int level_num);
    static sf::Vector2f get_player_start_pos(int level_num);
private:
    static std::vector<std::vector<int>> create_level_1();
    static std::vector<std::vector<int>> create_level_2();
};
