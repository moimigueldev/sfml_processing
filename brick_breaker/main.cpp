#include <iostream>
#include <SFML/Graphics.hpp>
#include "Slider.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

sf::Vector2f windowSize = sf::Vector2f(1500.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
Slider slider = Slider(sf::Vector2f( windowSize.x / 2, windowSize.y - 100 ));
Ball ball = Ball(sf::Vector2f( windowSize.x / 2, windowSize.y / 2 ));
Brick brick = Brick(sf::Vector2f( windowSize.x / 2, windowSize.y / 2 - 200 ));


sf::Vector2f brickSize = sf::Vector2f(80.0f, 15.0f);

const float PADDING = 10.0f; // Define a padding value

int cols = (windowSize.x - PADDING) / (brickSize.x + PADDING);
int rows = (windowSize.y / 2 - PADDING) / (brickSize.y + PADDING);

// Components:
    // Bottom slider
    // The ball
    // Walls (different color per row)


int main() {


  std::vector<Brick> bricks;


 for (int j = 0; j < rows; j++) {
    for (int i = 0; i < cols; i++) {
        float x = PADDING + i * (brickSize.x + PADDING);
        float y = PADDING + j * (brickSize.y + PADDING);
        bricks.push_back(Brick(sf::Vector2f(x, y)));
    }
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

     switch (event.key.code) {
        case sf::Keyboard::Left:
          slider.addAcc(sf::Vector2f(-1.0f, 0.0f));
          break;
        case sf::Keyboard::Right:
          slider.addAcc(sf::Vector2f(1.0f, 0.0f));
          break;
        default:
          break;
          
      }

    }


    window.clear(bgColor);


     slider.checkBallCollision(ball);

     for (int i = 0; i < bricks.size(); i++) {
       bricks[i].draw(window);
     }


    ball.update(windowSize);
    ball.draw(window);


    slider.update(windowSize);
    slider.draw(window);
   

    window.display();

  }

  return 0;
}
