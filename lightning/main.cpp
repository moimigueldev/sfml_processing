#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

sf::Vector2f windowSize = WindowUtility::windowSize;
sf::Color bgColor = WindowUtility::bgColor;
const int FRAMERATE = WindowUtility::FRAMERATE;

int main() {
  Game game = Game();

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    WindowUtility::handleEvents(window);
    window.clear(bgColor);

    game.draw(window);

    window.display();
  }

  return 0;
}
