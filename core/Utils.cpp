#include "Utils.hpp"
#include "Config.hpp"

float Utils::get_centered_x(const float &obj_width) {
    return (static_cast<float>(Config::WINDOW_WIDTH) / 2) - (obj_width / 2);
}