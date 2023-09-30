#include <iostream>
#include <SFML/Graphics.hpp>
#include "Slider.hpp"
#include "Ball.hpp"

sf::Vector2f windowSize = sf::Vector2f(1500.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
Slider slider = Slider(sf::Vector2f( windowSize.x / 2, windowSize.y - 100 ));
Ball ball = Ball(sf::Vector2f( windowSize.x / 2, windowSize.y / 2 ));


// Components:
    // Bottom slider
    // The ball
    // Walls (different color per row)


int main() {

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
    
      if(event.type == sf::Event::Closed) {
        window.close();
      }

     switch (event.key.code) {
        case sf::Keyboard::Left:
          slider.addAcc(sf::Vector2f(-2.0f, 0.0f));
          break;
        case sf::Keyboard::Right:
          slider.addAcc(sf::Vector2f(2.0f, 0.0f));
          break;
        default:
          break;
          
      }

    }


    window.clear(bgColor);


 slider.checkBallCollision(ball);
    ball.update(windowSize);
    ball.draw(window);


    slider.update(windowSize);
    slider.draw(window);
   

    window.display();

  }

  return 0;
}
