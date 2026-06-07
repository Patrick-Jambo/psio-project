#include "Animation.hpp"

Animation::Animation(sf::Sprite &target_sprite, float frame_duration, bool loop) :
    sprite(target_sprite), frame_duration(frame_duration), loop(loop)
{

}

void Animation::add_frame(const sf::IntRect &rect) {
    frames.emplace_back(rect);

    if (frames.size() == 1) {
        sprite.setTextureRect(rect);
    }
}

void Animation::add_frame_line(int start_x, int start_y, int width, int height, int count, int spacing) {
    for (int i = 0; i < count; i++) {
        const int current_x = start_x + i * (width + spacing);
        add_frame(sf::IntRect(current_x, start_y, width, height));
    }
}

void Animation::update(float dt) {
    if (frames.empty() || finished) return;

    timer += dt;
    if (timer >= frame_duration) {
        timer -= frame_duration;

        if (current_frame + 1 < frames.size()) {
            current_frame++;
            sprite.setTextureRect(frames[current_frame]);
        } else {
            if (loop) {
                current_frame = 0;
                sprite.setTextureRect(frames[current_frame]);
            } else {
                finished = true;
            }
        }
    }
}

void Animation::reset() {
    timer = 0;
    current_frame = 0;
    finished = false;
    if (!frames.empty()) {
        sprite.setTextureRect(frames[0]);
    }
}