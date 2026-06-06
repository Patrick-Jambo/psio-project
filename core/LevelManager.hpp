#pragma once
#include <vector>

class LevelManager {
public:
    static std::vector<std::vector<int>> get_level(int level_num);
private:
    static std::vector<std::vector<int>> create_level_1();
    static std::vector<std::vector<int>> create_level_2();
};