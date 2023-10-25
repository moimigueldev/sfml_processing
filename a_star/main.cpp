#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"
#include "Grid.hpp"
#include "WindowUtility.hpp"
#include "utility.hpp"

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);

int main() {
  Grid grid = Grid(windowSize);
  Game game = Game(grid);

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                          "A* Pathfinder");
  window.setFramerateLimit(WindowUtility::FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    WindowUtility::handleCloseEvent(window, game, grid);

    window.clear(WindowUtility::bgColor);

    grid.draw(window);

    game.run();
    // game.resetColors(window);
    // game.drawOpenSet(window);
    // game.drawClosedSet(window);
    game.drawPath(window);

    window.display();
  }

  return 0;
}
