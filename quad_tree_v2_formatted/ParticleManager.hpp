#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Particle.hpp"
#include "QuadTree.hpp"

class ParticleManager {
 private:
 public:
  ParticleManager() {}

  static void updateAndDrawParticles(std::vector<Particle>& particles,
                                     sf::RenderWindow& window, QuadTree& tree) {
    for (Particle& particle : particles) {
      particle.update();
      particle.draw(window);
      tree.insert(particle);
      if (particle.highlight) {
        particle.highlight = false;
      }
    }
  }

  static void updateParticleIntersections(std::vector<Particle>& particles,
                                          QuadTree& tree) {
    for (Particle& particle : particles) {
      Circle range = Circle(particle.shape.getPosition(), particle.RADIUS * 2);
      std::vector<std::reference_wrapper<Particle> > found;
      tree.query(range, particle, found);
      for (int i = 0; i < found.size(); i++) {
        found[i].get().highlight = true;
      }
    }
  }

  static void updateBruteForceCollisions(std::vector<Particle>& particles) {
    for (int i = 0; i < particles.size(); i++) {
      for (int j = i + 1; j < particles.size(); j++) {
        // For simplicity, let's assume Particle has a method called
        // `intersects` that checks if two particles are touching or
        // overlapping.
        if (particles[i].intersects(particles[j])) {
          particles[i].highlight = true;
          particles[j].highlight = true;
        }
      }
    }
  }
};

