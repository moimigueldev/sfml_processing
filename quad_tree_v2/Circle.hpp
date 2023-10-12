#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Circle {
 private:
 public:
  sf::CircleShape shape;
  int radius;
  Circle(sf::Vector2f pos, int rad) {
    radius = rad;

    shape.setRadius(radius);
    shape.setPosition(pos);
    shape.setOrigin(radius, radius);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Green);
  }

  void draw(sf::RenderWindow& window) { window.draw(shape); }
};

