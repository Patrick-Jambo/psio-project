#pragma once
#include <string>
#include "../nlohmann/json.hpp"

class SaveManager {
public:
    static void load(const std::string& filepath);
    static void save();
    static std::string get_intertitle(int level_num);
    static void update_best_time(int level_num, double time);
    static void update_global_records(int final_deaths, float final_time, bool& new_death_rec, bool& new_time_rec);
    static void load_settings();
    static void save_settings();

    static int get_global_death_record();
    static float get_global_time_record();


private:
    static nlohmann::json save_data;
    static std::string current_filepath;
};