#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <random>

class RainDrop {
  private:
    sf::RectangleShape line;
    sf::Vector2f recSize = sf::Vector2f(0.0f, 35.0f);
    sf::Vector2f vel = sf::Vector2f(0.0f, 0.5f);
    sf::Vector2f acc = sf::Vector2f(0.0f, 0.0f);
    const int MAX_ROTATION_POS = 45;
    const int MAX_ROTATION_NEG = -45;

  public:
    float degrees = 0;
   RainDrop(sf::Vector2f pos) {

    // Reinitialize random height for depth effect
    recSize.y = static_cast<float>( genRandomInt(5, 20));
    vel.y += recSize.y * 0.5;
    int thickness = vel.y * 0.20;


    line.setPosition(pos.x, pos.y);
    line.setSize(recSize);
    line.setOrigin(recSize.x / 2, recSize.y / 2);
    line.setFillColor(sf::Color::Transparent);
    line.setOutlineThickness(thickness);
    line.setOutlineColor(sf::Color::White);
    line.rotate(degrees);
   }

    void update(sf::Vector2f windowSize) {

      vel += acc;
    
      line.move(vel);


      sf::Vector2f pos = line.getPosition();


      if(pos.y > windowSize.y){
        line.setPosition(pos.x, -recSize.y);
      }

      if(pos.x > windowSize.x){
        line.setPosition(0, pos.y);
      }


      if(pos.x < 0){
        line.setPosition(windowSize.x, pos.y);
      }

     if(degrees > MAX_ROTATION_POS) {
            degrees -= 0.05;
        line.setRotation(degrees);  // Apply the updated rotation to the line
        } else if(degrees < MAX_ROTATION_NEG) {
            degrees += 0.05;
        line.setRotation(degrees);  // Apply the updated rotation to the line
        }


     degrees *= 0.9;
     line.rotate(degrees);





      vel.x *= 0.95;


      acc *= 0.05f;
    
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


   void rotate(float newDegree) {
     degrees += newDegree;
        if (degrees > 360) degrees -= 360;  // Ensure degrees stays between 0 and 360
        if (degrees < 0) degrees += 360;
        line.setRotation(degrees);  // Use setRotation instead of rotate
   }

   void addAcc(sf::Vector2f force) {
    acc += force;
   }
};

