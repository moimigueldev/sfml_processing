#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

sf::Vector2i windowSize = WindowUtility::windowSize;

int main() {
  Game game = Game();
  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Pong");
  window.setFramerateLimit(WindowUtility::FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    WindowUtility::handleEvents(window);
    window.clear(WindowUtility::bgColor);
    game.draw(window);

    window.display();
  }

  return 0;
}
