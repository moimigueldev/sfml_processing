#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Cell.hpp"
#include <memory>
#include <vector>


sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int CELL_WIDTH = 50;

const int cols = floor( windowSize.x / CELL_WIDTH );
const int rows = floor( windowSize.y / CELL_WIDTH );
const int gridSize = cols * rows;






int main() {


  std::vector< std::unique_ptr< Cell > > grid;

  for (int j = 0; j < rows; ++j) {
    // std::cout << j << std::endl;

     for (int i = 0; i < cols; ++i) {
       // std::cout << j << std::endl;
       grid.push_back(std::make_unique<Cell>(i, j));
     } 
  }
       std::cout << grid.size() << std::endl;


  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);
  

 
  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
    
      if(event.type == sf::Event::Closed) {
        window.close();
      }

    }

    window.clear(bgColor);

   for (size_t i = 0; i < grid.size(); i++) {
     grid[i]->draw(window);
     
   }
    


    window.display();

  }

  return 0;
}
