#pragma once
#include <string>
#include "../nlohmann/json.hpp"

class SaveManager {
public:
    static void load(const std::string& filepath);
    static void save();
    static std::string get_intertitle(int level_num);
    static void update_best_time(int level_num, double time);
    static void load_settings();
    static void save_settings();


private:
    static nlohmann::json save_data;
    static std::string current_filepath;
};