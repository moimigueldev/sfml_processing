#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Particle.hpp"

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

  // In the Circle class:
  bool contains(const Particle& particle) const {
    sf::Vector2f circleCenter = shape.getPosition();
    sf::Vector2f particlePos = particle.cords;

    float distance = std::sqrt(std::pow(circleCenter.x - particlePos.x, 2) +
                               std::pow(circleCenter.y - particlePos.y, 2));

    return distance < radius;
  }

  void draw(sf::RenderWindow& window) { window.draw(shape); }
};

