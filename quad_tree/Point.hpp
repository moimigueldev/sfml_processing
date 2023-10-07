#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Point {
 private:
  sf::Vector2f position;
  sf::CircleShape point;
  int radius = 8;

 public:
  float x;
  float y;
  Point(sf::Vector2f pos) {
    position = pos;
    point.setRadius(8);
    point.setFillColor(sf::Color::White);
    point.setOrigin(radius, radius);
    point.setPosition(position.x, position.y);

    x = position.x;
    y = position.y;
  }

  void draw(sf::RenderWindow& window) { window.draw(point); }
};

