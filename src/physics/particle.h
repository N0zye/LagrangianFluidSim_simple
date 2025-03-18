#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "configuration.h"
/* In order to use Verlet integration, we need:
    - The current position of the object
    - The previous position of the object
    - The acceleration of the object
*/

struct ParticleObject {
    sf::Vector2f position;
    sf::Vector2f position_old;
    sf::Vector2f acceleration;


    // just for now let's give them a random initial old

    explicit ParticleObject(const sf::Vector2f position, const sf::Vector2f v0) : position(position), position_old(position - (v0 * (conf::dt/static_cast<float>(conf::substeps))) ), acceleration(sf::Vector2f(0.0f, 0.0f)){}
    ParticleObject& operator=(const ParticleObject& other) {
        if (this != &other) {
            position = other.position;
            position_old = other.position_old;
            acceleration = other.acceleration;
        }
        return *this;
    }
    /* Verlet integration:
       x_{n+1} = 2x_n - x_{n-1} + a * dt^2
     */
    void update(const float dt) {
        const sf::Vector2f temp = position;
        position = (2.0f * position) - position_old + (acceleration * dt * dt);
        position_old = temp;
        acceleration = {0.0f, 0.0f};
    }
    void applyAcceleration(const sf::Vector2f a) {
        acceleration += a;
    }

    [[nodiscard]]
    float distanceTo(const ParticleObject& other) const{
        const sf::Vector2f distance = position - other.position;
        const float length = sqrtf(distance.x*distance.x + distance.y*distance.y);
        return length;
    }
};