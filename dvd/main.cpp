#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logo.hpp"
int windowHeight = 800;
int windowWidth = 1200;



int main() {



  sf::RenderWindow window (sf::VideoMode(windowWidth, windowHeight), "DVD");


  window.setFramerateLimit(60);


  // Logo logo(windowWidth/ 2, windowHeight / 2, 100, 50);
  Logo logo(windowWidth/ 2, windowHeight / 2, 250, 117);




  while(window.isOpen()) {

    sf::Event event;

    while (window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }


      if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::R) {
          logo.reset();
        }
      
      }
    }

    window.clear(sf::Color(255, 230, 130));

    logo.update(windowWidth, windowHeight);

    logo.draw(window);

    window.display();
  }
  
  return 0;
}
