#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

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

      // if(vel.x > MAX_VEL) {
      //   vel.x = MAX_VEL;
      // }



      slider.move(vel);

    
      checkPosition(windowSize, position);
      

      acc *= 0.9f;
      vel *= 0.9f;

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
    }

};

