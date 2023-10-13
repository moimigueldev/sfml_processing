#include <SFML/Graphics.hpp>
#include <iostream>

#include "Circle.hpp"
#include "EventUtils.hpp"
#include "Particle.hpp"
#include "ParticleManager.hpp"
#include "QuadTree.hpp"
#include "Rectangle.hpp"
#include "Utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
// sf::Vector2f windowSize = sf::Vector2f(100.0f, 50.0f);
sf::Color bgColor = sf::Color(0, 0, 0);
const int FRAMERATE = 60;
const int N_PARTICLES = 1000;

float currentTime = 0.0f;
static int frameCount = 0;

int main() {
  sf::Clock clock;

  std::vector<Particle> particles =
      Particle::initialize(N_PARTICLES, windowSize);

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

    ParticleManager::updateAndDrawParticles(particles, window, tree);
    ParticleManager::updateParticleIntersections(particles, tree);
    // ParticleManager::updateBruteForceCollisions(particles);

    // tree.draw(window);

    window.display();
  }

  return 0;
}
