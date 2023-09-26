#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <thread>
#include <chrono>


class Chime {
  
  private:
    sf::Vector2f chimeSize = sf::Vector2f(50, 50);
    sf::RectangleShape chime;
    sf::Vector2f windowSize;
    sf::Color chimeColor = sf::Color(142, 184, 229);
    sf::Vector2f velocity;
    bool finishedDelay = false;
    const float FRICTION = 0.999f;
    bool increase = false;

  public:
    Chime(sf::Vector2u windowDims, sf::Vector2f position, sf::Vector2f vel) {
     
      windowSize.x = static_cast<float>(windowDims.x);
      windowSize.y = static_cast<float>(windowDims.y);
      velocity.x = vel.x;
      velocity.y = vel.y;
      chime.setSize(chimeSize);
      chime.setFillColor(chimeColor);
      chime.setOrigin(chimeSize.x / 2, chimeSize.y / 2);
      chime.setPosition(position.x, position.y);
    }



void update() {
    // if(velocity.x < 1.0f) {
    //     increase = true;
    // }
    //
    // if(velocity.x > 8.0f) {
    //     increase = false;
    // }
    //
    // if(increase) {
    //     velocity.x *= 1.001; // Increase the velocity faster
    // }
    // else {
    //     velocity.x *= 0.999; // Decrease the velocity faster
    // }

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

    void setVelocity(sf::Vector2f newVel) {
      velocity.x = newVel.x;
      velocity.y = newVel.y;
    }

    sf::Vector2f getVelocity() {
      return velocity;
    }

    void setFinishedDelay(bool val) {
      finishedDelay = val;
    }


    bool getFinishedDelay() {
      return finishedDelay;
    }


};
