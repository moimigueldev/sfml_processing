#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);

int main() {
  Game game = Game();

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(WindowUtility::FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    WindowUtility::handleEvents(window);
    window.clear(WindowUtility::bgColor);

    window.display();
  }

  return 0;
}
