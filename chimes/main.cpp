#include <iostream>
#include <SFML/Graphics.hpp>
#include "Chime.hpp"
#include "Border.hpp"

sf::Vector2f windowSize = sf::Vector2f(1500.0f, 1200.0f);
sf::Vector2f borderSize = sf::Vector2f(750.0f, 1000.0f);
int frameRate = 60;

sf::Vector2f chimeSize = sf::Vector2f(50.0f, 50.0f);



int main() {
  

    
  // sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Chimes", sf::Style::Fullscreen);
  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Chimes");

  window.setFramerateLimit(frameRate);

  Border border = Border(window.getSize(), borderSize);

  sf::Vector2f borderSize = border.getSize();
  sf::Vector2f borderPosition = border.getPosition();

  float chimePosX = borderPosition.x - (borderSize.x / 2) + chimeSize.x;
  float chimePosY = borderPosition.y - (borderSize.y / 2) + chimeSize.y;



  Chime chime1 = Chime(window.getSize(), sf::Vector2f(chimePosX, chimePosY));


  // Main Loop
  while(window.isOpen()) {

    sf::Event event;


    if(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color(8, 7, 26));

    border.draw(window);

    chime1.update();
    chime1.draw(window);


    border.checkCollision(chime1);

    window.display();
    

  }




  return 0;
}
