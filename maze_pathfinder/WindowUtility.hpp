#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utility.hpp"

namespace WindowUtility {

sf::Color bgColor = sf::Color(38, 38, 38);
const int FRAMERATE = 15;

void handleEvents(sf::RenderWindow& window) {
  sf::Event event;

  if (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

}  // namespace WindowUtility

