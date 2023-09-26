#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.hpp"
#include<array>

sf::Vector2f windowSize = sf::Vector2f(1500.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int nCircles = 20;


int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 64; 

  std::array<std::unique_ptr<Circle>, nCircles> circles;



  
  int radius = 100;
  float speed = 0.035;
  for (int i = 0; i < nCircles; i++) {
    // circles[i] = Circle(windowSize, radius, speed);
    circles[i] = std::make_unique<Circle>(windowSize, radius, speed);
    radius += 25;
    speed -= 0.001;
  }

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML", sf::Style::Default, settings);
  window.setFramerateLimit(FRAMERATE);
  sf::Clock clock;

  int frameCount = 0;

  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
    
      if(event.type == sf::Event::Closed) {
        window.close();
      }

    }

    window.clear(bgColor);


    for (int i = 0; i < nCircles; i++) {
      circles[i]->update();
      circles[i]->draw(window);
    }



    window.display();
    frameCount++;
    if(clock.getElapsedTime().asSeconds() >= 1.0f) {

      std::cout << "FPS: " << frameCount << std::endl;
      frameCount = 0;
      clock.restart();
    }

  }

  return 0;
}



