#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <random>

class RainDrop {
  private:
    sf::RectangleShape line;
    sf::Vector2f recSize = sf::Vector2f(0.0f, 35.0f);
    sf::Vector2f vel = sf::Vector2f(0.0f, 6.0f);
    sf::Vector2f acc = sf::Vector2f(0.0f, 0.0f);

  public:
    int degrees = 0;
   RainDrop(sf::Vector2f pos) {

    // Reinitialize random height for depth effect
    recSize.y = static_cast<float>( genRandomInt(5, 35));

    line.setPosition(pos.x, pos.y);
    line.setSize(recSize);
    line.setOrigin(recSize.x / 2, recSize.y / 2);
    line.setFillColor(sf::Color::Transparent);
    line.setOutlineThickness(1);
    line.setOutlineColor(sf::Color::Red);
    line.rotate(degrees);
   }

    void update(sf::Vector2f windowSize) {

      vel += acc;
    
      line.move(vel);


      sf::Vector2f pos = line.getPosition();


      if(pos.y > windowSize.y){
        line.setPosition(pos.x, -recSize.y);
      }
      


      acc *= 0.0f;
    
    }

   void draw(sf::RenderWindow& window) {  
    window.draw(line);
   }


   static int genRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
   }

};

