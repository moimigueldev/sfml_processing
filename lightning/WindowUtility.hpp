#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utility.hpp"

namespace WindowUtility {

sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 100;
sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);

void handleEvents(sf::RenderWindow& window) {
  sf::Event event;

  if (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

}  // namespace WindowUtility

