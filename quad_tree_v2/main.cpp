#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Particle.hpp"
#include "QuadTree.hpp"
#include "Rectangle.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;

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
  std::vector<Particle> particles;

  Rectangle boundary =
      Rectangle(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), windowSize);
  QuadTree tree = QuadTree(boundary, 4);

  for (int i = 0; i < 100; i++) {
    float posX = genRandomInt(0, windowSize.x);
    float posY = genRandomInt(0, windowSize.y);
    particles.push_back(sf::Vector2f(posX, posY));
    bool inserted = tree.insert(particles[i]);
  }

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    sf::Event event;

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(bgColor);

    for (int i = 0; i < particles.size(); i++) {
      particles[i].update();
      particles[i].draw(window);
    }

    tree.draw(window);

    window.display();
  }

  return 0;
}
