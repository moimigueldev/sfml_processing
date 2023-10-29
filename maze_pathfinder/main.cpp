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

  Utility::FPSCounter fpsCounter;  // Step 1: Create an instance of FPSCounter

  sf::Clock clock;  // Create a clock to measure elapsed time

  // Main Loop
  while (window.isOpen()) {
    WindowUtility::handleEvents(window);
    window.clear(WindowUtility::bgColor);

    game.draw(window);

    window.display();
    float elapsedTime =
        clock.restart().asSeconds();  // Get the elapsed time in seconds
    fpsCounter.update(elapsedTime);
  }

  return 0;
}
