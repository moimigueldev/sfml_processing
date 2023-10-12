#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Particle.hpp"

class Rectangle {
 private:
  sf::CircleShape centerPoint;

 public:
  sf::RectangleShape shape;
  Rectangle(sf::Vector2f position, sf::Vector2f size) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::Transparent);

    centerPoint.setRadius(5);
    centerPoint.setPosition(shape.getPosition().x, shape.getPosition().y);
    centerPoint.setFillColor(sf::Color::Red);
  }

  bool contains(Particle point) {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    return (point.cords.x > pos.x - size.x / 2 &&
            point.cords.x < pos.x + size.x / 2 &&
            point.cords.y > pos.y - size.y / 2 &&
            point.cords.y < pos.y + size.y / 2);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(centerPoint);
  }
};

