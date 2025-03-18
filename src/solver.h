#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "physics/constraints.h"
#include "physics/particle.h"
#include "physics/collisions.h"
#include "physics/grid.h"

class Solver {
public:
    explicit Solver() = default;
    explicit Solver(const sf::Vector2f rect_size, const sf::Vector2f rect_position){
        const uint32_t particles_x = rect_size.x / (conf::particle_radius * 2);
        const uint32_t particles_y = rect_size.y / (conf::particle_radius * 2);
        for(uint32_t i = 0; i < particles_x; i++) {
            for(uint32_t j = 0; j < particles_y; j++) {
                const sf::Vector2f position = sf::Vector2f(rect_position.x + conf::particle_radius * (1 + 2 * i),
                                                           rect_position.y + conf::particle_radius * (1 + 2 * j));
                addParticle(ParticleObject{position, {0.0f, 0.0f}});
            }
        }
    }

    void addParticle(const ParticleObject& particle) {
        m_particles.push_back(particle);
    }

    void addConstraint(const ConstraintLine& constrain) {
        m_constraint_lines.push_back(constrain);
    }
    void addConstraint(const ConstraintRectangle& constrain) {
        m_constraint_rectangles.push_back(constrain);
    }

    [[nodiscard]]
    std::vector<ConstraintLine> getConstraintLines() const{
        return m_constraint_lines;
    }
    [[nodiscard]]
    std::vector<ConstraintRectangle> getConstraintRectangles() const{
        return m_constraint_rectangles;
    }

    void update(const float dt) {
        const float substep_dt = dt / static_cast<float>(conf::substeps);
        for (uint8_t i = 0; i < conf::substeps; i++) {
            applyGravity();
            updateParticles(substep_dt);
            applyConstraints();
            addParticlesToGrid();
            checkCollisions();
        }
    }

    [[nodiscard]]
    std::vector<ParticleObject> getParticles() const{
        return m_particles;
    }

private:
    Grid m_grid;
    std::vector<ParticleObject> m_particles;
    std::vector<ConstraintLine> m_constraint_lines;
    std::vector<ConstraintRectangle> m_constraint_rectangles;

    void addParticlesToGrid() {
        m_grid.clear();
        uint32_t i = 0;
        for (const ParticleObject& particle : m_particles) {
            if (particle.position.x > conf::particle_radius && particle.position.x < conf::window_size_f.x - conf::particle_radius &&
                particle.position.y > conf::particle_radius && particle.position.y < conf::window_size_f.y - conf::particle_radius) {
                m_grid.placeParticle(particle.position, i);
                }
            ++i;
        }
    }

    void applyGravity() {
        for (auto& particle : m_particles) {
            particle.applyAcceleration({0.0f, conf::gravity});
        }
    }

    void updateParticles(const float dt) {
        for (auto & m_particle : m_particles) {
            m_particle.update(dt);
        }
    }

    void checkCollisions() {
        for(uint32_t i = 1; i < m_grid.size().x-1; i++) {
            for(uint32_t j = 1; j<m_grid.size().y-1; j++) {
                Cell cell = m_grid.getCell(i, j);
                for(int8_t dx = -1; dx <= 1; dx++) {
                    for(int8_t dy = -1; dy <= 1; dy++) {
                        Cell neighborCell = m_grid.getCell(i + dx, j + dy);
                        checkCollisionsCells(cell, neighborCell);
                    }
                }
            }
        }
    }

    void checkCollisionsCells(const Cell& cell1, const Cell& cell2) {
        for(auto& index1 : cell1.indices) {
            for(auto& index2 : cell2.indices) {
                if(index1 != index2) {
                    if(collide(m_particles[index1], m_particles[index2])) resolveCollision(m_particles[index1], m_particles[index2]);
                }
            }
        }
    }

    void applyConstraints() {
        for(auto& particle : m_particles) {
            for(auto& line : m_constraint_lines) {
                if (collide(particle, line)) resolveCollision(particle, line);
            }
            for(auto& rectangle : m_constraint_rectangles) {
                if (collide(particle, rectangle)) resolveCollision(particle, rectangle);
            }
        }
    }
};