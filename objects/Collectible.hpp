#pragma once
#include "Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"

class Collectible : public Entity {
public:
    Collectible(sf::Vector2f pos, ResourceManager& resources);
    ~Collectible() override = default;

    void update(float dt, const TileMap& level_map) override;
    sf::FloatRect get_hitbox() const override;

    bool is_collected() const { return state != State::IDLE; }
    bool is_completely_done() const { return state == State::FINISHED; }
    void collect();

private:
    sf::Sprite sprite;
    bool collected = false;
    float bounce_timer = 0.0f;

    enum class State {
        IDLE,
        BURNING,
        FINISHED
    };

    State state = State::IDLE;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};