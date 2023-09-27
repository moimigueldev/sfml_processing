#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boid.hpp"
#include <memory>

using std::cout;
using std::endl;

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int N_BOIDS = 20;


int main() {


  std::vector<std::unique_ptr<Boid> > boids;


  for (int i = 0; i < N_BOIDS; i++) {
    int randomX = Boid::genRandomInt(0, windowSize.x);
    int randomY = Boid::genRandomInt(0, windowSize.y);
    boids.push_back(std::make_unique<Boid>(sf::Vector2f(randomX, randomY)));
  }


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
boids[0]->highlightRadius(window);
    boids[0]->seperation(boids, 0);

    for (int i = 0; i < N_BOIDS; i++) {
      boids[i]->update(windowSize);
      boids[i]->draw(window);
    }

    
    window.display();
  }

  return 0;
}
