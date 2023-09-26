#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include "Chime.hpp"
#include "Border.hpp"
#include <thread>
#include <chrono>

sf::Vector2f windowSize = sf::Vector2f(1500.0f, 1200.0f);
sf::Vector2f borderSize = sf::Vector2f(750.0f, 1000.0f);
int frameRate = 60;
const int nChimes = 14;
sf::Vector2f chimeVel = sf::Vector2f(6.09f, 0.0f);
sf::Vector2f chimeSize = sf::Vector2f(50.0f, 50.0f);


int main() {
  

  
    
  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Chimes");
  window.setFramerateLimit(frameRate);
  
  std::array<std::unique_ptr<Chime>, nChimes> chimes;


  Border border = Border(window.getSize(), borderSize);

  sf::Vector2f borderSize = border.getSize();
  sf::Vector2f borderPosition = border.getPosition();
  float padding = 20;
  float chimePosX = borderPosition.x - (borderSize.x / 2) + chimeSize.x;
  float chimePosY = borderPosition.y - (borderSize.y / 2) + chimeSize.y;
  float chimeBuffer  = chimeSize.y + padding;

  for (int i = 0; i < nChimes; ++i) {
    std::cout << i << std::endl;

    if(i == 0) {
      chimes[i] = std::make_unique<Chime>(window.getSize(), sf::Vector2f(chimePosX, chimePosY), chimeVel);
      chimeVel.x -= 0.01;
      continue;
    } 

    chimes[i] = std::make_unique<Chime>(window.getSize(), sf::Vector2f(chimePosX, chimePosY + chimeBuffer), chimeVel);
    chimeBuffer += chimeSize.y + padding;
    chimeVel.x -= 0.01;

  }



  std::thread([&chimes]() {
    for (int i = 0; i < nChimes; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      chimes[i]->setFinishedDelay(true);
    }
   

  std::cout << "Complete" << std::endl;

  }).detach();

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

    



    for (int i = 0; i < nChimes; i++) {
      if(chimes[i]->getFinishedDelay()) {
        chimes[i]->update();
      }
      chimes[i]->draw(window);
     
    }


    for (int i = 0; i < nChimes; i++) {
      border.checkCollision(chimes[i]);
    }

    window.display();

  }
  return 0;
}
