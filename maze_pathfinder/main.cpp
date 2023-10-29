#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(900.0f, 900.0f);

int main() {
  Game game = Game(windowSize);

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                          "Maze Pathfinder");
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
