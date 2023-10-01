#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <array>

class Brick {
  private:
    sf::Vector2f brickSize = sf::Vector2f(80.0f, 25.0f);


  public:
    sf::RectangleShape brick;
    Brick(sf::Vector2f pos, sf::Color color) {
      brick.setPosition(pos.x, pos.y);
      brick.setSize(brickSize);
      brick.setOrigin(brickSize.x / 2, brickSize.y / 2);
      brick.setFillColor(color);
    }


  

    void draw(sf::RenderWindow& window) {
      window.draw(brick);
    }



    bool checkBallCollision(Ball& ball) {
      sf::Vector2f ballPosition = ball.ball.getPosition();
      sf::Vector2f brickPos = brick.getPosition();
      int radius = ball.RADIUS;


     // Top Edge
      if (ballPosition.y + radius > brickPos.y - brickSize.y / 2 && 
          ballPosition.y + radius < brickPos.y &&
          ballPosition.x + radius > brickPos.x - brickSize.x / 2 &&
          ballPosition.x - radius < brickPos.x + brickSize.x / 2) {
          std::cout << "Collision with top edge!" << std::endl;
          ball.vel.y *= -1;
          return true;
      }

      // Left Edge
      if (ballPosition.x + radius > brickPos.x - brickSize.x / 2 && 
          ballPosition.x + radius < brickPos.x &&
          ballPosition.y + radius > brickPos.y - brickSize.y / 2 &&
          ballPosition.y - radius < brickPos.y + brickSize.y / 2) {
          std::cout << "Collision with left edge!" << std::endl;
          ball.ball.setPosition(brickPos.x - brickSize.x / 2 - radius, ballPosition.y);
          ball.vel.x *= -1;
          return true;
      }

      // Right Edge
      if (ballPosition.x - radius < brickPos.x + brickSize.x / 2 && 
          ballPosition.x - radius > brickPos.x &&
          ballPosition.y + radius > brickPos.y - brickSize.y / 2 &&
          ballPosition.y - radius < brickPos.y + brickSize.y / 2) {
          std::cout << "Collision with right edge!" << std::endl;
          ball.vel.x *= -1;
          return true;
      }

     

      // Bottom Edge (unlikely in a brick breaker game, but included for completeness)
      if (ballPosition.y - radius < brickPos.y + brickSize.y / 2 && 
          ballPosition.y - radius > brickPos.y &&
          ballPosition.x + radius > brickPos.x - brickSize.x / 2 &&
          ballPosition.x - radius < brickPos.x + brickSize.x / 2) {
          std::cout << "Collision with bottom edge!" << std::endl;
          ball.vel.y *= -1;
          return true;
      }

      return false;
}


};


