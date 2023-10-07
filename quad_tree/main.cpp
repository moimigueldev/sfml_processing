
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Point.hpp"
#include "QuadTree.hpp"

using std::cout;
using std::endl;

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;

int genRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

int main() {
  Point point = Point(sf::Vector2f(200, 200));

  Rectangle boundary =
      Rectangle(sf::Vector2f(windowSize.x / 2, windowSize.y / 2),
                sf::Vector2f(windowSize.x, windowSize.y));

  QuadTree qtree = QuadTree(boundary, 5);

  auto pos = boundary.shape.getPosition();

  std::vector<Point> points;

  for (int i = 0; i < 100; i++) {
    sf::Vector2f position =
        sf::Vector2f(static_cast<float>(genRandomInt(0, windowSize.x)),
                     static_cast<float>(genRandomInt(0, windowSize.y)));
    points.push_back(position);
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

      if (event.type == sf::Event::MouseButtonPressed) {
        float mouseX = event.mouseButton.x;
        float mouseY = event.mouseButton.y;
        cout << "Pressed " << mouseX << " " << mouseY << endl;
        qtree.insert(sf::Vector2f(mouseX, mouseY));
      }
    }

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //   float mouseX = event.mouseButton.x;
    //   float mouseY = event.mouseButton.y;
    //   cout << "Pressed " << mouseX << " " << mouseY << endl;
    //   qtree.insert(sf::Vector2f(mouseX, mouseY));
    // }

    window.clear(bgColor);

    // boundary.draw(window);
    qtree.draw(window);

    window.display();
  }

  return 0;
}
