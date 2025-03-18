#include <SFML\Graphics.hpp>
#include "configuration.h"
#include "events.h"
#include "solver.h"
#include "renderer.h"
#include <iostream>

int main() {
    auto window = sf::RenderWindow{ {conf::window_size.x, conf::window_size.y}, "Fluids (hopefully)", sf::Style::Fullscreen };
    window.setFramerateLimit(conf::max_FPS);
    // Solver solver{{400, 200}, {800, 100}};
    Solver solver;
    solver.addConstraint(ConstraintRectangle({conf::window_size_f.x - 40.0f, conf::window_size_f.y-40.0f}, {20, 20}));
    const Renderer renderer(window);

    while (window.isOpen()){
        processEvents(window);

        // Add particles
        if(solver.getParticles().size() < 10000) {
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 2*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 4*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 6*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 8*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 10*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 12*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 14*conf::particle_radius}, {2000.0f, 0.0f}});
            solver.addParticle(ParticleObject{sf::Vector2f{400.0f, 100.0f + 16*conf::particle_radius}, {2000.0f, 0.0f}});
        }
        solver.update(conf::dt);

        // Draw everything
        window.clear(sf::Color::Black);
        renderer.render(solver);
        window.display();
    }

    return 0;
}