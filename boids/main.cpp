#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boid.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;


int main() {

  Boid boid = Boid(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));


  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
    
      if(event.type == sf::Event::Closed) {
        window.close();
      }

    }

    window.clear(bgColor);


    boid.update(windowSize);
    boid.draw(window);

    window.display();

  }

  return 0;
}
