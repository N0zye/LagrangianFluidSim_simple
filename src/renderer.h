#pragma once
#include <SFML/Graphics.hpp>
#include "solver.h"

class Renderer {
public:
    explicit Renderer(sf::RenderWindow& window) : m_window(window) {
    }
    void render(const Solver& solver) const {
        renderParticles(solver);
        renderConstraints(solver);
    }
private:
    sf::RenderWindow& m_window;

    void renderParticles(const Solver& solver) const {
        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f, 1.0f);
        for (const auto& particles = solver.getParticles(); const auto& particle : particles) {
            circle.setPosition(particle.position);
            circle.setScale(conf::particle_radius, conf::particle_radius);
            m_window.draw(circle);
        }
    }

    void renderConstraints(const Solver& solver) const {
        for (const auto& constraint : solver.getConstraintLines()) {
            sf::Vertex line[] = {
                sf::Vertex(constraint.p1),
                sf::Vertex(constraint.p2)
            };
            m_window.draw(line, 2, sf::Lines);
        }

        for (const auto& constraint : solver.getConstraintRectangles()) {
            const auto& lines = constraint.getLines();
            for (const auto& l : lines) {
                sf::Vertex line[] = {
                    sf::Vertex(l.p1),
                    sf::Vertex(l.p2)
                };
                m_window.draw(line, 2, sf::Lines);
            }
        }
    }
};
