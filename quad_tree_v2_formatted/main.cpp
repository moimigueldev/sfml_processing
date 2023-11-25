#include <SFML/Graphics.hpp>
#include <cmath>    // For sin(), cos()
#include <cstdlib>  // For rand()
#include <iostream>
#include <vector>

#include "Circle.hpp"
#include "EventUtils.hpp"
#include "Particle.hpp"
#include "ParticleManager.hpp"
#include "QuadTree.hpp"
#include "Rectangle.hpp"
#include "Utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(0, 0, 0);
const int FRAMERATE = 60;
const int N_PARTICLES = 300;

int main() {
  sf::Clock clock;

  std::vector<Particle> particles;
  std::vector<sf::Vector2f> velocities(N_PARTICLES);

  // Initialize particles and velocities
  for (int i = 0; i < N_PARTICLES; ++i) {
    float posX = Utility::genRandomInt(0, windowSize.x);
    float posY = Utility::genRandomInt(0, windowSize.y);
    float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;
    float speed = 20.0f + static_cast<float>(rand() % 10);  // Increased speed
    velocities[i] =
        sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

    particles.push_back(Particle(sf::Vector2f(posX, posY)));
  }

  Rectangle boundary =
      Rectangle(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);
  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                          "QuadTree");
  window.setFramerateLimit(FRAMERATE);

  Utility::FPSCounter fpsCounter;

  // Main Loop
  while (window.isOpen()) {
    float elapsedTime = clock.restart().asSeconds();
    fpsCounter.update(elapsedTime);
    EventUtils::handleCloseEvent(window);
    EventUtils::handleMousePressEvents(window, particles);

    QuadTree tree = QuadTree(boundary, 15);

    window.clear(bgColor);

    // Update particles and insert them into the QuadTree
    for (int i = 0; i < N_PARTICLES; ++i) {
      particles[i].shape.move(velocities[i] * elapsedTime);
      tree.insert(particles[i]);
    }

    // Draw particles
    for (auto& particle : particles) {
      window.draw(particle.shape);
    }

    tree.draw(window);
    window.display();
  }

  return 0;
}

