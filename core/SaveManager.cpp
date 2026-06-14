#include "../core/SaveManager.hpp"
#include "../ui/Settings.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

nlohmann::json SaveManager::save_data;
std::string SaveManager::current_filepath;

void SaveManager::load(const std::string& filepath) {
    current_filepath = filepath;
    std::ifstream file(filepath);

    if (file.is_open()) {
        file >> save_data;
        file.close();
        std::cout << "LOADED FILE: " << filepath << std::endl;

        load_settings();
    } else {
        std::cerr << "CANNOT LOAD FILE: " << filepath << ". CREATING A NEW ONE..." << std::endl;
        save_data = nlohmann::json::object();
    }
}

void SaveManager::save() {
    std::ofstream file(current_filepath);
    if (file.is_open()) {
        file << save_data.dump(4);
        file.close();
        std::cout << "GAME DATA SUCCESSFULLY SAVED!" << std::endl;
    }
}

std::string SaveManager::get_intertitle(int level_num) {
    std::string lvl_key = std::to_string(level_num);
    if (save_data.contains(lvl_key) && save_data[lvl_key].contains("intertitle_text")) {
        return save_data[lvl_key]["intertitle_text"];
    }
    return "ENTERING LEVEL " + lvl_key + "...";
}

void SaveManager::update_best_time(int level_num, double time) {
    std::string lvl_key = std::to_string(level_num);

    if (save_data.contains(lvl_key)) {
        double current_best = save_data[lvl_key]["best_time"];

        double rounded_time = std::round(time * 100.0) / 100.0;

        if (current_best == -1.0 || rounded_time < current_best) {
            save_data[lvl_key]["best_time"] = rounded_time;
            save();
            std::cout << "NEW TIME RECORD FOR LEVEL: " << level_num << ": " << rounded_time << "s" << std::endl;
        }
    }
}

void SaveManager::load_settings() {
    if (save_data.contains("settings")) {
        auto& s = save_data["settings"];
        if (s.contains("music_enabled")) Settings::music_enabled = s["music_enabled"];
        if (s.contains("god_mode_enabled")) Settings::god_mode_enabled = s["god_mode_enabled"];
        if (s.contains("hitboxes_enabled")) Settings::hitboxes_enabled = s["hitboxes_enabled"];
        std::cout << "SETTINGS LOADED INTO THE GAME." << std::endl;
    }
}

void SaveManager::save_settings() {
    save_data["settings"]["music_enabled"] = Settings::music_enabled;
    save_data["settings"]["god_mode_enabled"] = Settings::god_mode_enabled;
    save_data["settings"]["hitboxes_enabled"] = Settings::hitboxes_enabled;
}

void SaveManager::update_global_records(int final_deaths, float final_time, bool& new_death_rec, bool& new_time_rec) {
    int old_death_record = save_data["global_stats"].value("death_record", -1);

    if (old_death_record == -1 || final_deaths < old_death_record) {
        save_data["global_stats"]["death_record"] = final_deaths;
        new_death_rec = true;
    } else {
        new_death_rec = false;
    }

    float old_time_record = save_data["global_stats"].value("best_time", -1.0f);

    if (old_time_record == -1.0f || final_time < old_time_record) {
        save_data["global_stats"]["best_time"] = final_time;
        new_time_rec = true;
    } else {
        new_time_rec = false;
    }

    save();
}

int SaveManager::get_global_death_record() { return save_data["global_stats"].value("death_record", -1); }
float SaveManager::get_global_time_record() { return save_data["global_stats"].value("best_time", -1.0f); }