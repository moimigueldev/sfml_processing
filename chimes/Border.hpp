#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Chime.hpp"


class Border {
  
  private:
    sf::Vector2f borderSize;
    sf::RectangleShape border;
    sf::Vector2f windowSize;
    sf::Color borderColor = sf::Color(24, 24, 36);
    int outlineWidth = 10;

  public:
    Border(sf::Vector2u windowDims, sf::Vector2f size) {
      windowSize.x = static_cast<float>(windowDims.x);
      windowSize.y = static_cast<float>(windowDims.y);
      borderSize.x = size.x;
      borderSize.y = size.y;
      border.setSize(borderSize);
      border.setFillColor(sf::Color::Transparent);
      border.setOutlineThickness(outlineWidth);
      border.setOutlineColor(borderColor);
      border.setOrigin(borderSize.x / 2, borderSize.y / 2);
      border.setPosition(windowSize.x / 2, windowSize.y / 2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(border);
    }


    bool checkCollision(Chime& chime) {
      sf::Vector2f chimePosition = chime.getPosition();
      int outlineBuffer = 5;

      if(chimePosition.x + outlineWidth * 2 + outlineBuffer>= border.getPosition().x + borderSize.x / 2 ) {
        std::cout << "Hit" << std::endl;
        chime.reversexVel();
      }

      if(chimePosition.x - outlineWidth * 2 - outlineBuffer<= border.getPosition().x - borderSize.x / 2 ) {
        std::cout << "Hit" << std::endl;
        chime.reversexVel();
      }

      return false;
    }


    sf::Vector2f getPosition() {
        return border.getPosition();
    }

    sf::Vector2f getSize() {
        return border.getSize();
    }



};
