#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Shape {
  private:
    sf::RectangleShape shape;
    sf::Vector2f gravity = sf::Vector2f(0.0f, 2.0f);
    sf::Vector2f acceleration = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
    float speed = 6.0f;
    sf::Vector2f windowDims;

  public:
    Shape(sf::Vector2f size, sf::Color color, sf::Vector2f windowSize) {
      shape.setSize(size);
      shape.setFillColor(color);
      shape.setOrigin(size.x / 2, size.y / 2);
      shape.setPosition(windowSize.x / 2, windowSize.y / 2);
      windowDims = sf::Vector2f(windowSize);

    }


     void update() {
      sf::Vector2f position = shape.getPosition();
      sf::Vector2f shapeSize = shape.getSize();

      acceleration += gravity;
      velocity += acceleration;

      shape.move(velocity);


      // Reset accelaration for the next frame
      acceleration *= 0.0f;

      if(( position.y + shapeSize.y / 2 ) + 10 > windowDims.y) {
         shape.setPosition(windowDims.x / 2, windowDims.y - shapeSize.y / 2);
        velocity.y = 0.0f; // You can also make it bounce by multiplying with a negative value
      }

      
      ;
    }


    void draw(sf::RenderWindow& window) {
      window.draw(shape);
    } 


    void adjustVelocity(float x, float y) {
      std::cout << "In here" << x << std::endl;
      velocity.x += x;
      velocity.y += y;
    }



};

