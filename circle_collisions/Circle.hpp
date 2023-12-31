#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>



class Circle {
  
  private:
  
    sf::CircleShape shape;
    sf::CircleShape center;
    sf::VertexArray line;

    sf::Vector2f windowSize;
    sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f acceleration = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f gravity = sf::Vector2f(0.0f, 1.0f);
    float angularVel = 0.0f;
    float angularAcc = 0.0f;
    float mass;

    const float TERMINAL_VELOCITY = 30.0f;
    const int RADIUS = genRandomInt(10, 100);
    const int OUTLINE_THICKNESS = 3;
    const float FRICTION = 1.009;
    const float RESTITUTION = 0.8; // Keeps 80% of its momentum
    const double PI = 3.141592653589793;
    




  public:
    Circle(sf::Vector2f windowDims) {
      windowSize = windowDims;
      mass = PI * pow(RADIUS, 2);
      std::cout << mass << std::endl;
      setupShapes();

    }

   void update() {
        acceleration += gravity;
        velocity += acceleration;

      
        angularVel += angularAcc;


        velocity.x = velocity.x > TERMINAL_VELOCITY ? TERMINAL_VELOCITY : velocity.x;
        velocity.y = velocity.y > TERMINAL_VELOCITY ? TERMINAL_VELOCITY : velocity.y;

        shape.rotate(angularVel);
        shape.move(velocity);

        // Border Checks
        borderCheck();

        acceleration *= 0.0f;
        velocity = velocity / FRICTION;

        angularVel = angularVel / FRICTION;

        angularAcc = 0.0f;
    }


    void draw(sf::RenderWindow& window) {
      window.draw(shape);

      center.setPosition(shape.getPosition().x, shape.getPosition().y);
      window.draw(center);

      // line[0].position = sf::Vector2f(shape.getPosition().x, shape.getPosition().y);
      // line[1].position = sf::Vector2f(shape.getPosition().x + RADIUS, shape.getPosition().y);
      float rotationInRadians = shape.getRotation() * (PI / 180.0);
      float xOffset = RADIUS * cos(rotationInRadians);
      float yOffset = RADIUS * sin(rotationInRadians);
      line[0].position = sf::Vector2f(shape.getPosition().x, shape.getPosition().y);
      line[1].position = sf::Vector2f(xOffset,yOffset) + shape.getPosition();
     


      window.draw(line);
    }


    int genRandomInt(int low, int high) {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distrib(low, high);
      return (distrib(gen));
    }


   void adjustAcc(float x, float y) {
    acceleration.x += x;
    acceleration.y += y;

    // Determine the rotation direction based on the direction of the applied force
    if (x > 0) {
        angularAcc = -1.0f;  // Rotate clockwise
    } else if (x < 0) {
        angularAcc = 1.0f;  // Rotate counterclockwise
    }
}



    void setupShapes() {

      center.setRadius(5);
      center.setOrigin(5, 5);
      center.setFillColor(sf::Color::Red);
      center.setPosition(windowSize.x / 2, windowSize.y / 2);

      shape.setRadius(RADIUS);
      shape.setOrigin(RADIUS, RADIUS);
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineThickness(OUTLINE_THICKNESS); // Set border width
      shape.setOutlineColor(sf::Color(genRandomInt(0, 255), genRandomInt(0, 255), genRandomInt(0, 255))); // Set border color
      shape.setPosition(windowSize.x / 2, windowSize.y / 2);


      line.setPrimitiveType(sf::Lines);
      line.resize(2);
      line[0].color = sf::Color::Red;
      line[1].color = sf::Color::Red;
     

    }



    void borderCheck() {
       if(shape.getPosition().y + RADIUS + OUTLINE_THICKNESS > windowSize.y) {
        velocity.y = RESTITUTION * (velocity.y * -1.0f);
        shape.setPosition(shape.getPosition().x, windowSize.y - RADIUS - OUTLINE_THICKNESS);
      }


      if(shape.getPosition().y - RADIUS - OUTLINE_THICKNESS < 0) {
        velocity.y = RESTITUTION * (velocity.y * -1.0f);

        shape.setPosition(shape.getPosition().x , RADIUS + OUTLINE_THICKNESS);
      }

       if(shape.getPosition().x + RADIUS + OUTLINE_THICKNESS > windowSize.x) {
        velocity.x = RESTITUTION * (velocity.x * -1.0f);
        shape.setPosition(windowSize.x - RADIUS - OUTLINE_THICKNESS, shape.getPosition().y);
      }
      if(shape.getPosition().x - RADIUS - OUTLINE_THICKNESS < 0) {
        velocity.x = RESTITUTION * (velocity.x * -1.0f);
        shape.setPosition (RADIUS +  OUTLINE_THICKNESS, shape.getPosition().y);
      }
    }



    void resetPos(sf::Vector2f newPos) {
      shape.setPosition(newPos.x, newPos.y);
    }


    sf::Vector2f getPos() {
      return shape.getPosition();
    }

    int getRadius() {
      return RADIUS;
    }

    sf::Vector2f getVelocity() {
      return velocity;
    }

    void setVelocity(sf::Vector2f newVelocity) {
      velocity.x = newVelocity.x;
      velocity.y = newVelocity.y;
    }

    float getMass() {
      return mass;
    }

    void setPosition(sf::Vector2f newPos) {
      shape.setPosition(newPos.x, newPos.y);
    }

};
