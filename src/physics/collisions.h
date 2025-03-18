#pragma once

#include "particle.h"
#include "constraints.h"

inline bool collide(const ParticleObject& p1, const ParticleObject& p2) {
    return p1.distanceTo(p2) < 2*conf::particle_radius;
}

inline bool collide(const ParticleObject& p1, const ConstraintLine& cl) {
    return cl.distanceToPoint(p1.position) < conf::particle_radius;
}

inline bool collide(const ParticleObject& p1, const ConstraintRectangle& cr) {
    const ConstraintLine closest_line = cr.getClosestLine(p1.position);
    return collide(p1, closest_line);
}

inline void resolveCollision(ParticleObject& p1, ParticleObject& p2) {
    constexpr float reduction_factor = 0.5f;
    const sf::Vector2f normal = (p1.position - p2.position) / p1.distanceTo(p2);
    const float overlap = 2*conf::particle_radius - p1.distanceTo(p2);
    p1.position += 0.5f* normal * overlap * reduction_factor;
    p2.position -= 0.5f* normal * overlap * reduction_factor;
}

inline void resolveCollision(ParticleObject& p1, const ConstraintLine& cl) {
    const sf::Vector2f normal = cl.getNormal();
    const float overlap = conf::particle_radius - cl.distanceToPoint(p1.position);
    p1.position += normal * overlap;
}

inline void resolveCollision(ParticleObject& p1, const ConstraintRectangle& cr) {
    const ConstraintLine closest_line = cr.getClosestLine(p1.position);
    resolveCollision(p1, closest_line);
}