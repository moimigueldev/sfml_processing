#include <iostream>
#include <SFML/Graphics.hpp>


int windowHeight = 400;
int windowWidth = 600;



int main() {

sf::ContextSettings settings;
settings.antialiasingLevel = 8;  


	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Window Hello World", sf::Style::Default, settings);


  window.setFramerateLimit(60);

  sf::Clock clock;

  int frameCount = 0;



  sf::CircleShape circle(50); // circle with a radious of 50px;
  circle.setFillColor(sf::Color::Green);
  circle.setOrigin(50, 50);
  circle.setPosition(window.getSize().x / 2, window.getSize().y / 2);


  sf::CircleShape point(5);
  point.setFillColor(sf::Color::Red);
  point.setOrigin(5, 5);
  point.setPosition(window.getSize().x / 2, window.getSize().y / 2);


	// Main loop
	while (window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}



		window.clear(sf::Color(128, 128, 128));

    // float circleRightEdge = circle.getPosition().x + circle.getRadius();
    // if( circleRightEdge < windowWidth) {
    //   circle.move(2, 0);
    // }
    

    if(event.type == sf::Event::KeyPressed) {
      
      switch (event.key.code) {
        case sf::Keyboard::Left:
          circle.move(-1, 0);
          break;
        case sf::Keyboard::Right:
          circle.move(1, 0);
          break;
        case sf::Keyboard::Up:
          circle.move(0, -1);
          break;
        default:
          circle.move(0, 1);
          break;
          
      }

    }



    window.draw(circle);
    window.draw(point);
		window.display();


    frameCount++;
    if(clock.getElapsedTime().asSeconds() >= 1.0f) {

    std::cout << "FPS: " << frameCount << std::endl;
    frameCount = 0;
    clock.restart();
    }
	}

return 0;
}
