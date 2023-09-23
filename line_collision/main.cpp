#include <iostream>
#include <SFML/Graphics.hpp>
#include "shape.hpp"

int windowWidth = 1500;
int windowHeight = 800;
sf::Vector2f windowSize = sf::Vector2f(windowWidth, windowHeight);
sf::Vector2f shapeSize = sf::Vector2f(100.0f, 200.0f);
float movingSpeed = 2.0f;



void handleCollision(Shape& shape1, Shape& shape2) {
    // Calculate the overlap or penetration depth
    float overlap = (shape1.getSize().x / 2 + shape2.getSize().x / 2) - abs(shape1.getPosition().x - shape2.getPosition().x);

    // Adjust the positions of the shapes to resolve the overlap
    float correction = overlap / 2.0f;
    shape1.repositionShape(sf::Vector2f(shape1.getPosition().x - correction, shape1.getPosition().y));
    shape2.repositionShape(sf::Vector2f(shape2.getPosition().x + correction, shape2.getPosition().y));

    // Adjust the velocities based on the masses and the collision response
    float tempVel = shape1.getVelocity().x;
    float otherMass = shape2.getMass();
    float mass = shape1.getMass();

    shape1.setVelocity(sf::Vector2f(
        (tempVel * (mass - otherMass) + 2.0f * otherMass * shape2.getVelocity().x) / (mass + otherMass),
        shape1.getVelocity().y
    ));

    shape2.setVelocity(sf::Vector2f(
        (shape2.getVelocity().x * (otherMass - mass) + 2.0f * mass * tempVel) / (mass + otherMass),
        shape2.getVelocity().y
    ));
}



int main() {
  Shape shape1 = Shape(shapeSize, sf::Color(255, 76, 176), windowSize);
  Shape shape2 = Shape(sf::Vector2f(10.0f, 200.0f), sf::Color(176, 76, 255), windowSize);
  // Shape shape2 = Shape(shapeSize, sf::Color(176, 76, 255), windowSize);
  shape1.repositionShape(sf::Vector2f( windowSize.x / 2 - 300, windowSize.y / 2 ));
  shape2.repositionShape(sf::Vector2f( windowSize.x / 2 + 300, windowSize.y / 2 ));

  sf::RenderWindow window(sf::VideoMode( windowWidth, windowHeight ), "Line Collision");

  window.setFramerateLimit(60);

  // Main Loop 
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }

      if(event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Left:
            shape1.adjustAcc(-movingSpeed, 0.0f);
            break;
          case sf::Keyboard::Right:
            shape1.adjustAcc(movingSpeed, 0.0f);
            break;
          case sf::Keyboard::Up:
            shape1.adjustAcc(0.0f, -movingSpeed);
            break;
          default:
            shape1.adjustAcc(0.0f, movingSpeed);
            break;
        }
      }
    }


    window.clear(sf::Color(68, 70, 83));
    
    shape1.update(shape2);
    shape1.draw(window);
    
    shape2.update(shape1);
    shape2.draw(window);


  
    // handleCollision(shape1, shape2);


    window.display();
    

  }

  
  

  return 0;
}
