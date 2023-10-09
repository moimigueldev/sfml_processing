
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>

#include "Point.hpp"
#include "QuadTree.hpp"

using std::cout;
using std::endl;

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
auto framerate = 0.0f;

sf::Font font;

int genRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

int main() {
  sf::Clock clock;
  float frameTime = 0.0f;

  sf::Font font;
  if (!font.loadFromFile("font.ttf")) {
    std::cerr << "Can not load font" << endl;
    return -1;
  }

  sf::Text text;
  text.setFont(font);  // font is a sf::Font
  text.setString(std::to_string(framerate));
  text.setCharacterSize(24);  // in pixels, not points!
  text.setFillColor(sf::Color::Red);
  text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  text.setPosition(50, 50);  // Set position to (50, 50)

  Rectangle boundary =
      Rectangle(sf::Vector2f(windowSize.x / 2, windowSize.y / 2),
                sf::Vector2f(windowSize.x, windowSize.y));

  auto pos = boundary.shape.getPosition();

  QuadTree qtree = QuadTree(boundary, 5);
  std::vector<Point> points;

  for (int i = 0; i < 100; i++) {
    sf::Vector2f position =
        sf::Vector2f(static_cast<float>(genRandomInt(0, windowSize.x)),
                     static_cast<float>(genRandomInt(0, windowSize.y)));
    points.push_back(Point(position));
    qtree.insert(position);
  }

  // 500 is 8 fps;
  for (int i = 0; i < 500; i++) {
    sf::Vector2f position =
        sf::Vector2f(static_cast<float>(genRandomInt(0, windowSize.x)),
                     static_cast<float>(genRandomInt(0, windowSize.y)));
    points.push_back(Point(position));
    qtree.insert(position);
  }

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    sf::Time elapsed =
        clock.restart();  // Restart the clock and get the elapsed time
    frameTime = elapsed.asSeconds();     // Convert the elapsed time to seconds
    float framerate = 1.0f / frameTime;  // Compute the framerate

    // Optionally, print the framerate to the console

    sf::Event event;

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      //
      // if (event.type == sf::Event::MouseButtonPressed) {
      //   float mouseX = event.mouseButton.x;
      //   float mouseY = event.mouseButton.y;
      //   cout << "Pressed " << mouseX << " " << mouseY << endl;
      //   points.push_back(Point(sf::Vector2f(mouseX, mouseY)));
      //   qtree.insert(sf::Vector2f(mouseX, mouseY));
      // }
    }
    qtree = QuadTree(boundary, 4);
    for (int i = 0; i < points.size(); i++) {
      qtree.insert(sf::Vector2f(points[i].x, points[i].y));
      points[i].highlight = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      float offsetX = genRandomInt(-10, 10);
      float offsetY = genRandomInt(-10, 10);
      sf::Vector2i mousePos =
          sf::Mouse::getPosition(window);  // Get the current mouse position
      float mouseX = static_cast<float>(mousePos.x) + offsetX;
      float mouseY = static_cast<float>(mousePos.y) + offsetY;
      cout << "Pressed " << mouseX << " " << mouseY << endl;
      points.push_back(Point(sf::Vector2f(mouseX, mouseY)));
      qtree.insert(sf::Vector2f(mouseX, mouseY));
    }

    window.clear(bgColor);

    // boundary.draw(window);
    qtree.draw(window);

    // for (int i = 0; i < points.size(); i++) {
    //   points[i].update();
    //   Point& currentPoint = points[i];
    //
    //   for (int j = 0; j < points.size(); j++) {
    //     Point& other = points[j];
    //     if (i != j && currentPoint.intersects(other)) {
    //       currentPoint.highlight = true;
    //       break;
    //     } else {
    //       currentPoint.highlight = false;
    //     }
    //   }
    //
    //   points[i].draw(window);
    // }

    for (int i = 0; i < points.size(); i++) {
      Circle range = Circle(points[i].x, points[i].y, points[i].radius * 2);

      std::vector<Point> found;
      std::vector<Point> pointsInRange = qtree.query(range, found);

      for (int j = 0; j < found.size(); j++) {
        Point& other =
            found[j];  // use 'j' instead of 'i' to index into 'found'
        if (i != j && points[i].intersects(other)) {
          points[i].highlight = true;
        } else {
          points[i].highlight = false;
        }
      }

      points[i].update();
      points[i].draw(window);
    }

    // for (int i = 0; i < points.size(); i++) {
    //   sf::CircleShape p;
    //   p.setRadius(3);
    //   p.setOrigin(3, 3);
    //   p.setOutlineColor(sf::Color::Green);
    //   p.setPosition(points[i].x, points[i].y);
    //   window.draw(p);
    // }
    //

    framerate = 1.0f / frameTime;

    text.setString(std::to_string(framerate));
    window.draw(text);
    window.display();
  }

  return 0;
}
