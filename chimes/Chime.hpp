#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Chime {
  
  private:
    sf::Vector2f chimeSize = sf::Vector2f(50, 50);
    sf::RectangleShape chime;
    sf::Vector2f windowSize;
    sf::Color chimeColor = sf::Color(142, 184, 229);
    sf::Vector2f velocity = sf::Vector2f(2.0f, 0.0f);

  public:
    Chime(sf::Vector2u windowDims, sf::Vector2f position) {
      windowSize.x = static_cast<float>(windowDims.x);
      windowSize.y = static_cast<float>(windowDims.y);
      chime.setSize(chimeSize);
      chime.setFillColor(chimeColor);
      chime.setOrigin(chimeSize.x / 2, chimeSize.y / 2);
      chime.setPosition(position.x, position.y);
    }



    void update() {

      chime.move(velocity);

    }

    void draw(sf::RenderWindow& window) {
        window.draw(chime);
    }


    void reversexVel() {
      velocity.x *= -1.0f;
    }

    sf::Vector2f getPosition() {
        return chime.getPosition();
    }


};
