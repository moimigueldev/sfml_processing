#include <iostream>
#include <SFML/Graphics.hpp>
#include "shape.hpp"

int windowWidth = 800;
int windowHeight = 600;
sf::Vector2f windowSize = sf::Vector2f(windowWidth, windowHeight);
sf::Vector2f shapeSize = sf::Vector2f(100.0f, 100.0f);

Shape shape1 = Shape(shapeSize, sf::Color(255, 76, 176), windowSize);

int main() {
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
            shape1.adjustVelocity(-10.0f, 0.0f);
            break;
          case sf::Keyboard::Right:
            shape1.adjustVelocity(10.0f, 0.0f);
            break;
          case sf::Keyboard::Up:
            shape1.adjustVelocity(0.0f, -10.0f);
            break;
          default:
            shape1.adjustVelocity(0.0f, 10.0f);
            break;
        }
      }
    }


    window.clear(sf::Color(68, 70, 83));
    
    shape1.update();
    shape1.draw(window);
    window.display();
    

  }
  

  return 0;
}
