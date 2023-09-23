
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>



class Circle {

  private:
    int radius;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;



  public:
    Circle() {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distrib(10, 50);
      std::uniform_int_distribution<> widthRange(radius, 1600 - radius);
      std::uniform_int_distribution<> heightRange(radius, 1000 - radius);
      std::uniform_int_distribution<> colorRange(0, 255);
      std::uniform_int_distribution<> startingVelocity(0, 9);
      speed = 6.0f;
      radius = distrib(gen);
      // std::cout << radius << std::endl;
      shape.setRadius(radius);
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineThickness(5);
      shape.setOutlineColor(sf::Color(colorRange(gen), colorRange(gen), colorRange(gen)));
      shape.setOrigin(radius, radius);
      shape.setPosition(widthRange(gen), heightRange(gen));

      
      
      float randX = speed + static_cast<float>(startingVelocity(gen) / 10.0f);
      float randY = speed + static_cast<float>(startingVelocity(gen) / 10.0f);

      if(randX > 6.5) {
        randX = -randX;
      }
      if(randY > 6.5) {
        randY = -randY;
      }

      velocity = sf::Vector2f(randX, randY);
      // velocity = sf::Vector2f(0.0f, -9.0f);
      // std::cout << velocity.x << ": -> " << velocity.y << std::endl;
    }

    void update(int windowWidth, int windowHeight) {
      sf::Vector2f position = shape.getPosition();


      if(position.x > windowWidth) {
        shape.setPosition(radius, position.y);
      }

      if(position.x < 0 ) {
        shape.setPosition(windowWidth - radius, position.y);
      }

      if(position.y > windowHeight) {
        shape.setPosition(position.x,radius);
      }

      if(position.y < 0 ) {
        shape.setPosition(position.x, windowHeight - radius);
      }



      shape.move(velocity);
    }



    void draw(sf::RenderWindow& window) {
      window.draw(shape);
    }





};
