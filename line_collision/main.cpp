#include <iostream>
#include <SFML/Graphics.hpp>
#include "shape.hpp"

int windowWidth = 1500;
int windowHeight = 600;
sf::Vector2f windowSize = sf::Vector2f(windowWidth, windowHeight);
sf::Vector2f shapeSize = sf::Vector2f(100.0f, 100.0f);
float movingSpeed = 2.0f;


int main() {
  Shape shape1 = Shape(shapeSize, sf::Color(255, 76, 176), windowSize);
  Shape shape2 = Shape(shapeSize, sf::Color(176, 76, 255), windowSize);
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


    window.display();
    

  }
  

  return 0;
}
