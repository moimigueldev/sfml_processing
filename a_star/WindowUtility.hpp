#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

namespace WindowUtility {

sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 20;

void handleCloseEvent(sf::RenderWindow& window, Game& game) {
  sf::Event event;

  if (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }

  // Check if the S key is pressed
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::S) {
    game.startGame = true;
  }
}

}  // namespace WindowUtility

