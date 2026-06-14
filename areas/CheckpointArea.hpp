#pragma once
#include "Area.hpp"
#include "../core/Animation.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../core/ResourceManager.hpp"
#include <memory>

class CheckpointArea : public Area {
public:
    CheckpointArea(const sf::FloatRect& bounds, const sf::Vector2f& respawn_pos, ResourceManager& resources);

    void on_enter(Game& game) override;
    void debug_hitbox() override;
    void update(float dt);

private:
    sf::Vector2f respawn_position;
    sf::Sprite campfire_sprite;
    std::unique_ptr<Animation> animator;

    enum class CampfireState {
        UNLIT,      // 1 klatka
        IGNITING,   // 2 klatki, odtwarzane raz
        BURNING     // 3 klatki, zapętlone
    };
    CampfireState campfire_state = CampfireState::UNLIT;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};