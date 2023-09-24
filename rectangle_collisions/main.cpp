#include <iostream>
#include <SFML/Graphics.hpp>
#include "shape.hpp"

int windowWidth = 1500;
int windowHeight = 800;
sf::Vector2f windowSize = sf::Vector2f(windowWidth, windowHeight);
sf::Vector2f shapeSize = sf::Vector2f(400.0f, 600.0f);
float movingSpeed = 2.0f;




int main() {
  Shape shape1 = Shape(shapeSize, sf::Color(255, 76, 176), windowSize);
  Shape shape2 = Shape(sf::Vector2f(100.0f, 150.0f), sf::Color(176, 76, 255), windowSize);
  // Shape shape2 = Shape(shapeSize, sf::Color(176, 76, 255), windowSize);
  shape1.repositionShape(sf::Vector2f( windowSize.x / 2 - 300, windowSize.y / 2 ));
  shape2.repositionShape(sf::Vector2f( windowSize.x / 2 + 300, windowSize.y / 2 ));

  Shape* selectedShape = &shape1;

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
            selectedShape->adjustAcc(-movingSpeed, 0.0f);
            break;
          case sf::Keyboard::Right:
            selectedShape->adjustAcc(movingSpeed, 0.0f);
            break;
          case sf::Keyboard::Up:
            selectedShape->adjustAcc(0.0f, -movingSpeed);
            break;
          default:
            selectedShape->adjustAcc(0.0f, movingSpeed);
            break;
        }
      }


      if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        bool shape1Selected = shape1.clickedInside(pixelPos);
        bool shape2Selected = shape2.clickedInside(pixelPos);



         if(shape1Selected) {
          std::cout << "Shape1Selected: " << shape1Selected << std::endl; 
          selectedShape = &shape1;
        }
        if(shape2Selected) {
          std::cout << "Shape2Selected: " << shape2Selected << std::endl;
          selectedShape = &shape2;
        }

      }
    }


    window.clear(sf::Color(68, 70, 83));
    
    // resolveOverlap(shape1, shape2);
    shape1.update(shape2);
    shape1.draw(window);
    
    shape2.update(shape1);
    shape2.draw(window);


  


    window.display();
    

  }

  
  

  return 0;
}
