#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Shape {
  private:
    sf::RectangleShape shape;
    sf::Vector2f gravity = sf::Vector2f(0.0f, 1.0f);
    sf::Vector2f acceleration = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f windowDims;
    sf::CircleShape shapePos;
    float mass;
    const float SPEED = 6.0f;
    const float TERMINAL_VELOCITY = 30.0f;
    const float FRICTION = 1.007;
    

  public:
    Shape(sf::Vector2f size, sf::Color color, sf::Vector2f windowSize) {
      shape.setSize(size);
      shape.setFillColor(color);
      shape.setOrigin(size.x / 2, size.y / 2);
      shape.setPosition(windowSize.x / 2, windowSize.y / 2);



     // Initialize the dot (shapePos)
      shapePos.setRadius(5);  // Set the radius of the dot
      shapePos.setFillColor(sf::Color::Green);  // Set the fill color of the dot
      shapePos.setOrigin(5, 5);  // Set the origin to the center of the dot
      shapePos.setPosition(shape.getPosition());



      mass = ( size.x * 0.1f ) + (size.y * 0.1f);
      std::cout << mass << std::endl; 


      windowDims = sf::Vector2f(windowSize);

    }


     void update(Shape& otherShape) {
      sf::Vector2f position = shape.getPosition();
      sf::Vector2f shapeSize = shape.getSize();

      acceleration += gravity;
      velocity += acceleration;


      velocity.x = velocity.x > TERMINAL_VELOCITY ? TERMINAL_VELOCITY : velocity.x;
      velocity.y = velocity.y > TERMINAL_VELOCITY ? TERMINAL_VELOCITY : velocity.y;


      shape.move(velocity);


      // Check for Collisions
     
      float dX = shape.getPosition().x - otherShape.getPosition().x;
      float combinedHalfWidths = shapeSize.x / 2 + otherShape.getSize().x / 2;
      if(abs(dX) < combinedHalfWidths){
        float tempVel = velocity.x;
        // velocity.x = otherShape.getVelocity().x;
        // otherShape.setVelocity(sf::Vector2f(tempVel, velocity.y));


        float otherMass = otherShape.getMass();

        velocity.x = (velocity.x *(mass - otherMass) / (mass + otherMass) ) + ((2.0f * otherMass) / (mass + otherMass) * otherShape.getVelocity().x);
        float otherVelocity = ((2 * mass) / (mass + otherMass) * tempVel) - ((mass - otherMass) / (mass + otherMass) * otherShape.getVelocity().x);
        otherShape.setVelocity(sf::Vector2f(otherVelocity, otherShape.getVelocity().y));
      }
      // Reset accelaration for the next frame
      acceleration *= 0.0f;

      if(( position.y + shapeSize.y / 2 ) + 10 > windowDims.y) {
        position.y = windowDims.y - shapeSize.y / 2;
        shape.setPosition(shape.getPosition().x, windowDims.y - shapeSize.y / 2);
        velocity.y *= -1;
      }


      // Check for right border
      if(position.x + shapeSize.x / 2 > windowDims.x) {
          shape.setPosition(windowDims.x - shapeSize.x / 2, shape.getPosition().y);
          velocity.x = -velocity.x;
      }


      if(position.x - shapeSize.x / 2 < 0.0f) {
          shape.setPosition(shapeSize.x / 2, shape.getPosition().y);
          // velocity.x = 0.0f; // Stop horizontal movement
          velocity.x = -velocity.x;
      }


      shapePos.setPosition(shape.getPosition().x, shape.getPosition().y);

      velocity = velocity / FRICTION;
      // velocity.x = 0.0f;
      // velocity.y = 0.0f;
    }


    void draw(sf::RenderWindow& window) {
      window.draw(shape);
      window.draw(shapePos);
    } 


    void adjustAcc(float x, float y) {
      acceleration.x += x;
      acceleration.y += y;
    }

    sf::Vector2f getPosition() {

      return shape.getPosition();
    }

    void repositionShape(sf::Vector2f newPos) {
      shape.setPosition(newPos.x, newPos.y);
    }

    sf::Vector2f getVelocity() {
      return velocity;
    }

    void setVelocity(sf::Vector2f newVel) {
      velocity.x = newVel.x;
      velocity.y = newVel.y;
    }


    float getMass() {
      return mass;
    }


    sf::Vector2f getSize() {
      return shape.getSize();
    }



};
