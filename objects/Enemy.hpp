#pragma once
#include "Entity.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"
#include <vector>

enum class EnemyMoveMode {
    PingPong, // A -> B -> A
    Path,     // A -> B -> C -> A
    Circular  // Obrót wokół osi
};

class Enemy : public Entity {
public:
    Enemy(std::vector<sf::Vector2f> waypoints, float speed, ResourceManager& resources, EnemyMoveMode mode = EnemyMoveMode::PingPong);
    Enemy(sf::Vector2f center, float radius, float angular_speed, ResourceManager& resources, float start_angle = 0.0f);

    ~Enemy() override = default;

    void update(float dt, const TileMap &level_map) override;
    sf::FloatRect get_hitbox() const override;

private:
    sf::Sprite enemy_sprite;
    EnemyMoveMode move_mode;
    float speed;

    // Zmienne dla PingPong i Path
    std::vector<sf::Vector2f> waypoints;
    size_t current_target_idx = 0;
    int direction_step = 1;

    // Zmienne dla Circular
    sf::Vector2f center_pos;
    float radius = 0.0f;
    float current_angle = 0.0f;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};