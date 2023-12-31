#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Circle.hpp"
#include "Particle.hpp"
#include "QuadTree.hpp"
#include "Rectangle.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
// sf::Vector2f windowSize = sf::Vector2f(100.0f, 50.0f);
sf::Color bgColor = sf::Color(0, 0, 0);
const int FRAMERATE = 60;
const int N_PARTICLES = 1000;

float currentTime = 0.0f;
static int frameCount = 0;

int genRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

template <typename T>
void consoleLog(T message) {
  std::cout << message << std::endl;
}

int main() {
  sf::Clock clock;
  std::vector<Particle> particles;

  Rectangle boundary =
      Rectangle(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);

  for (int i = 0; i < N_PARTICLES; i++) {
    float posX = genRandomInt(0, windowSize.x);
    float posY = genRandomInt(0, windowSize.y);
    particles.push_back(sf::Vector2f(posX, posY));
    // tree.insert(particles[i]);
  }

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                          "QuadTree");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    float elapsedTime = clock.restart().asSeconds();
    currentTime += elapsedTime;
    frameCount++;

    sf::Event event;

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      float offsetX = genRandomInt(-10, 10);
      float offsetY = genRandomInt(-10, 10);
      sf::Vector2i mousePos =
          sf::Mouse::getPosition(window);  // Get the current mouse position
      float mouseX = static_cast<float>(mousePos.x) + offsetX;
      float mouseY = static_cast<float>(mousePos.y) + offsetY;
      particles.push_back(Particle(sf::Vector2f(mouseX, mouseY)));
    }

    QuadTree tree = QuadTree(boundary, 15);

    window.clear(bgColor);

    for (int i = 0; i < particles.size(); i++) {
      particles[i].update();
      particles[i].draw(window);
      tree.insert(particles[i]);
      particles[i].highlight = false;
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
    if (currentTime >= 1.0f) {
      std::cout << "FPS: " << frameCount << std::endl;
      frameCount = 0;
      currentTime -= 1.0f;
    }
  }

  return 0;
}
