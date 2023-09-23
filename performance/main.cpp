#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.hpp"

int windowWidth = 1600;
int windowHeight = 1000;
int numOfCircles = 28000;


int main() {
  
  // Circle circles[numOfCircles];
  std::vector<Circle> circles(numOfCircles);
  sf::RenderWindow window (sf::VideoMode(windowWidth, windowHeight), "Circles");


  window.setFramerateLimit(60);


  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
      if(event.type == sf::Event::Closed) {
        window.close();
      }
    }



    window.clear(sf::Color(68, 70, 83));
   // for (int i = 0; i < numOfCircles; i++) {
   //    circles[i].update(windowWidth, windowHeight);
   //    circles[i].draw(window);
   //  }

   for (Circle& circle : circles) {
    circle.update(windowWidth, windowHeight);
    circle.draw(window);
}



    window.display();

  }

  return 0;
}




