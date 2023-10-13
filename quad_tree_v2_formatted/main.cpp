#include <SFML/Graphics.hpp>
#include <iostream>

#include "Circle.hpp"
#include "EventUtils.hpp"
#include "Particle.hpp"
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

    for (int i = 0; i < particles.size(); i++) {
      particles[i].update();
      particles[i].draw(window);
      tree.insert(particles[i]);
      if (particles[i].highlight) {
        particles[i].highlight = false;
      }
    }

    for (int i = 0; i < particles.size(); i++) {
      Circle range =
          Circle(particles[i].shape.getPosition(), particles[i].RADIUS * 2);

      std::vector<std::reference_wrapper<Particle> > found;

      tree.query(range, particles[i], found);

      for (int i = 0; i < found.size(); i++) {
        // std::cout << found[i].get().cords.x << std::endl;
        found[i].get().highlight = true;
      }

      // range.draw(window);
    }

    // for (int i = 0; i < particles.size(); i++) {
    //   for (int j = i + 1; j < particles.size(); j++) {
    //     // For simplicity, let's assume Particle has a method called
    //     // `intersects` that checks if two particles are touching or
    //     // overlapping.
    //     if (particles[i].intersects(particles[j])) {
    //       particles[i].highlight = true;
    //       particles[j].highlight = true;
    //     }
    //   }
    // }

    // tree.draw(window);

    window.display();
  }

  return 0;
}
