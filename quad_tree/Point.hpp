#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

float genRandomFloat(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> distrib(min, max);
  return distrib(gen);
}

class Point {
 private:
  sf::Vector2f position;
  sf::CircleShape point;

 public:
  int radius = 8;
  bool highlight = false;
  float x;
  float y;
  Point(sf::Vector2f pos) {
    position = pos;
    point.setRadius(8);
    point.setFillColor(sf::Color::Black);
    point.setOrigin(radius, radius);
    point.setPosition(position.x, position.y);

    x = position.x;
    y = position.y;
  }

  bool intersects(Point other) {
    float squaredDistance =
        (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
    float squaredDiameter =
        (radius + other.radius) * (radius + other.radius);  // Sum of radii
    return squaredDistance <= squaredDiameter;
  }

  void update() {
    float moveX = genRandomFloat(-1, 1);
    float moveY = genRandomFloat(-1, 1);

    point.move(sf::Vector2f(moveX, moveY));

    x = point.getPosition().x;
    y = point.getPosition().y;
  }

  void draw(sf::RenderWindow& window) {
    if (highlight) {
      point.setFillColor(sf::Color::White);
    } else {
      point.setFillColor(sf::Color::Black);
    }
    window.draw(point);
  }
};

