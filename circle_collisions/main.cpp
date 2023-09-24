#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.hpp"

sf::Vector2f windowDims = sf::Vector2f(1000, 800);
sf::Color bgColor = sf::Color(68, 70, 83);



const float MOVING_SPEED = 2.0f;

int main() {


  Circle circle1 = Circle(windowDims);
  
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
    

    window.display();

  }
  return 0;
}
