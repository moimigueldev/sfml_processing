#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <array>

class Slider {
  private:
    sf::Vector2f sliderSize = sf::Vector2f(200.0f, 15.0f);
    sf::Vector2f vel;
    sf::Vector2f acc;
    const float MAX_VEL = 40.0f;


  public:
    sf::RectangleShape slider;
    Slider(sf::Vector2f pos) {
      slider.setPosition(pos.x, pos.y);
      slider.setSize(sliderSize);
      slider.setOrigin(sliderSize.x / 2, sliderSize.y / 2);
      slider.setFillColor(sf::Color::White);
    }


    void update(sf::Vector2f windowSize) {
      sf::Vector2f position = slider.getPosition();

      vel+=acc;
      slider.move(vel);

      checkPosition(windowSize, position);
      

      acc *= 0.93f;
      vel *= 0.90f;

    }

    void draw(sf::RenderWindow& window) {
      window.draw(slider);
    }


    void checkPosition(sf::Vector2f windowSize, sf::Vector2f position) {
      if(position.x - sliderSize.x / 2 < 0) {
        nullVelAcc();
        slider.setPosition(sliderSize.x / 2, position.y);
      }

      if(position.x + sliderSize.x / 2 > windowSize.x) {
        nullVelAcc();
        slider.setPosition(windowSize.x - sliderSize.x / 2, position.y);
      }
    }


    void addAcc(sf::Vector2f force) {
      acc += force;
    }


    void nullVelAcc() {
      vel.x = 0.0f;
      acc *= 0.0f;
 
    }


    bool checkBallCollision(Ball& ball) {
      sf::Vector2f ballPosition = ball.ball.getPosition();
      sf::Vector2f sliderPos = slider.getPosition();
      int radius = ball.RADIUS;


     // Top Edge
      if (ballPosition.y + radius > sliderPos.y - sliderSize.y / 2 && 
          ballPosition.y + radius < sliderPos.y &&
          ballPosition.x + radius > sliderPos.x - sliderSize.x / 2 &&
          ballPosition.x - radius < sliderPos.x + sliderSize.x / 2) {
          std::cout << "Collision with top edge!" << std::endl;
          ball.vel.y *= -1;
          return true;
      }

      // Left Edge
      if (ballPosition.x + radius > sliderPos.x - sliderSize.x / 2 && 
          ballPosition.x + radius < sliderPos.x &&
          ballPosition.y + radius > sliderPos.y - sliderSize.y / 2 &&
          ballPosition.y - radius < sliderPos.y + sliderSize.y / 2) {
          std::cout << "Collision with left edge!" << std::endl;
          ball.ball.setPosition(sliderPos.x - sliderSize.x / 2 - radius, ballPosition.y);
          ball.vel.x *= -1;
          return true;
      }

      // Right Edge
      if (ballPosition.x - radius < sliderPos.x + sliderSize.x / 2 && 
          ballPosition.x - radius > sliderPos.x &&
          ballPosition.y + radius > sliderPos.y - sliderSize.y / 2 &&
          ballPosition.y - radius < sliderPos.y + sliderSize.y / 2) {
          std::cout << "Collision with right edge!" << std::endl;
          ball.vel.x *= -1;
          return true;
      }

     

      // Bottom Edge (unlikely in a brick breaker game, but included for completeness)
      if (ballPosition.y - radius < sliderPos.y + sliderSize.y / 2 && 
          ballPosition.y - radius > sliderPos.y &&
          ballPosition.x + radius > sliderPos.x - sliderSize.x / 2 &&
          ballPosition.x - radius < sliderPos.x + sliderSize.x / 2) {
          std::cout << "Collision with bottom edge!" << std::endl;
          ball.vel.y *= -1;
          return true;
      }

      return false;
}


};

