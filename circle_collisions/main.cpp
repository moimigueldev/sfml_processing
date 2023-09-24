#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Circle.hpp"

sf::Vector2f windowDims = sf::Vector2f(1000, 800);
sf::Color bgColor = sf::Color(68, 70, 83);

const float MOVING_SPEED = 2.0f;



bool detectCollission(Circle& shape1, Circle& shape2) {

  const float RESTITUTION = 0.8; // Keeps 80% of its momentum

  int radius1 = shape1.getRadius();
  int radius2 = shape2.getRadius();
  sf::Vector2f position1 = shape1.getPos();
  sf::Vector2f position2 = shape2.getPos();


  float distance =( sqrt(pow( position2.x - position1.x, 2) + pow(position2.y - position1.y ,2)));
  if(distance <= radius1 + radius2) {

    sf::Vector2f vel1 = shape1.getVelocity();
    sf::Vector2f vel2 = shape2.getVelocity();
    float mass1 = shape1.getMass();
    float mass2 = shape2.getMass();

    std::cout << distance << std::endl;


   
    float finalvel1X = ((mass1 - mass2) * vel1.x + 2 * mass2 * vel2.x) / (mass1 + mass2);
    float finalvel1Y = ((mass1 - mass2) * vel1.y + 2 * mass2 * vel2.y) / (mass1 + mass2);

    float finalvel2X = ((mass1 - mass2) * vel2.x + 2 * mass2 * vel1.x) / (mass1 + mass2);
    float finalvel2Y = ((mass1 - mass2) * vel2.y + 2 * mass2 * vel1.y) / (mass1 + mass2);

    


    shape1.adjustAcc(finalvel1X, finalvel1Y);
    shape2.adjustAcc(finalvel2X, finalvel2Y);
   // Separation step
float overlap = abs(radius1 + radius2 - distance);
sf::Vector2f separationDirection = (position1 - position2) / distance; // Normalize the direction
shape1.setPosition(position1 + (overlap * (mass2 / (mass1 + mass2))) * separationDirection);
shape2.setPosition(position2 - (overlap * (mass1 / (mass1 + mass2))) * separationDirection);

    
  }

  



  return false;
}

int main() {


  Circle circle1 = Circle(windowDims);
  Circle circle2 = Circle(windowDims);

  circle1.resetPos(sf::Vector2f( circle1.getPos().x - 100, circle1.getPos().y ));
  circle2.resetPos(sf::Vector2f( circle2.getPos().x + 100, circle2.getPos().y ));
  
  sf::RenderWindow window(sf::VideoMode(windowDims.x, windowDims.y), "Circle Collisions");

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
            circle1.adjustAcc(-MOVING_SPEED, 0.0f);
            break;
          case sf::Keyboard::Right:
            circle1.adjustAcc(MOVING_SPEED, 0.0f);
            break;
          case sf::Keyboard::Up:
            circle1.adjustAcc(0.0f, -MOVING_SPEED);
            break;
          default:
            circle1.adjustAcc(0.0f, MOVING_SPEED);
            break;
        }
      }



    }

    window.clear(bgColor);

    circle1.update();
    circle1.draw(window);
    circle2.update();
    circle2.draw(window);


    detectCollission(circle1, circle2);
    

    window.display();

  }
  return 0;
}
