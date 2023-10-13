#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

int randInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

class Particle {
 private:
 public:
  sf::CircleShape shape;
  int RADIUS = 8;
  sf::Vector2f cords;
  bool highlight = false;
  Particle(sf::Vector2f pos) {
    shape.setRadius(RADIUS);
    shape.setPosition(pos);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::Transparent);

    updateCords();
  }

  void update() {
    float randX = randInt(-1, 1);
    float randY = randInt(-1, 1);
    shape.move(randX, randY);

    updateCords();
  }

  void updateCords() {
    cords.x = shape.getPosition().x;
    cords.y = shape.getPosition().y;
  }

  void draw(sf::RenderWindow& window) {
    if (highlight) {
      shape.setFillColor(sf::Color::Red);
    } else {
      shape.setFillColor(sf::Color::Transparent);
    }

    window.draw(shape);
  }
};

