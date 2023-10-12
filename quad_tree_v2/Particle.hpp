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
  sf::CircleShape shape;

 public:
  int RADIUS = 2;
  sf::Vector2f cords;
  Particle(sf::Vector2f pos) {
    shape.setRadius(RADIUS);
    shape.setPosition(pos);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::Transparent);

    updateCords();
  }

  void update() {
    float randX = randInt(-3, 3);
    float randY = randInt(-3, 3);
    shape.move(randX, randY);

    updateCords();
  }

  void updateCords() {
    cords.x = shape.getPosition().x;
    cords.y = shape.getPosition().y;
  }

  void draw(sf::RenderWindow& window) { window.draw(shape); }
};

