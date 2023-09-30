#include <iostream>
#include <SFML/Graphics.hpp>
#include "RainDrop.hpp"

sf::Vector2i windowSize = sf::Vector2i(1000, 800);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int N_RAINDROP = 200;


// auto recSize = sf::Vector2f(200.0f, 0.0f);


void setupRain(std::vector<RainDrop>& rainList) {
  rainList.clear();
   for (int i = 0; i < N_RAINDROP; i++) {
    int randX = RainDrop::genRandomInt(0, windowSize.x);
    int randY = RainDrop::genRandomInt(0, windowSize.y);
    RainDrop newRainDrop = RainDrop(sf::Vector2f(static_cast<float>(randX), static_cast<float>(randY)));
    rainList.push_back(newRainDrop);
  }
}

int main() {

  // sf::CircleShape center(5);
  // center.setOrigin(5, 5);
  // center.setPosition(shape.getPosition().x, shape.getPosition().y);
  // center.setFillColor(sf::Color::Blue);

  int randX =  windowSize.x / 2;
  int randY =  windowSize.y / 2;

  // RainDrop rain = RainDrop(sf::Vector2f(static_cast<float>(randX), static_cast<float>(randY)));
  std::vector<RainDrop> rain;

  setupRain(rain);

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

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
          // circle.move(-1, 0);
          break;
        case sf::Keyboard::Right:
          // circle.move(1, 0);
          break;
        case sf::Keyboard::Up:
          // circle.move(0, -1);
          break;
        case sf::Keyboard::Down:
          // something
        default:
          setupRain(rain);
          break;
          
      }

    }



    }

    window.clear(bgColor);


    for (int i = 0; i < N_RAINDROP; i++) {
     rain[i].update(static_cast<sf::Vector2f>(windowSize));
     rain[i].draw(window);
    }





    window.display();

  }

  return 0;
}
