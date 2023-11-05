#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "WindowUtility.hpp"
#include "utility.hpp"

class Game {
 private:
  sf::RectangleShape leftPaddle;
  sf::RectangleShape rightPaddle;
  sf::CircleShape center;

 public:
  Game() { setupShapes(); }

  void draw(sf::RenderWindow& window) {
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    // window.draw(center);
  }

  void setupShapes() {
    sf::Vector2f size(30, 200);
    sf::Vector2i leftPaddlePosition(100, WindowUtility::windowSize.y / 2);
    sf::Vector2i rightPaddlePosition(WindowUtility::windowSize.x - 100,
                                     WindowUtility::windowSize.y / 2);

    leftPaddle.setPosition(leftPaddlePosition.x, leftPaddlePosition.y);
    leftPaddle.setSize(size);
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setOrigin(size.x / 2, size.y / 2);

    rightPaddle.setPosition(rightPaddlePosition.x, rightPaddlePosition.y);
    rightPaddle.setSize(size);
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setOrigin(size.x / 2, size.y / 2);

    center.setPosition(rightPaddlePosition.x, rightPaddlePosition.y);
    center.setRadius(5);
    center.setOrigin(5, 5);
    center.setFillColor(sf::Color::Red);
  }
};
