#pragma once

namespace conf {
    sf::Vector2u const window_size = {2560, 1440};
    sf::Vector2f const window_size_f = {2560.0f, 1440.0f};
    constexpr uint32_t max_FPS = 144;
    constexpr float dt = 1.0f / max_FPS;
    constexpr uint8_t substeps = 5;
    constexpr float particle_radius = 5.0f;
    constexpr float gravity = 2000.0f;
    constexpr float grid_size = 20.0f;
}