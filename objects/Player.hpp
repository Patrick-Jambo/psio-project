#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(sf::Vector2f start_pos, ResourceManager& resources);
    ~Player() override = default;

    void update(float dt) override;
    sf::FloatRect get_hitbox() const override;

private:
    void handle_input();
    sf::Sprite player_sprite;
    sf::Vector2f velocity;
    const float SPEED = 400;


    std::vector<sf::IntRect> animation_frames;
    size_t current_frame = 0;
    float animation_timer = 0.0f;
    const float FRAME_DURATION = 0.15f;
    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
