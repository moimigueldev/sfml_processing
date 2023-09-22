#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <SFML/Audio.hpp>


class Logo {

private: 
  sf::RectangleShape shape;
  sf::Vector2f velocity;
  float speed;
  sf::Vector2f startingPos;
  sf::Vector2f startingSize;
  sf::Texture dvdTexture;
  sf::SoundBuffer buffer;
  sf::Sound sound;

public:

  Logo(float x, float y, float width, float height) {
      startingSize = sf::Vector2f(width, height);
     startingPos = sf::Vector2f(x, y);
     reset();
     speed = 6.0f;

    if(!dvdTexture.loadFromFile("dvd.png")) {
  std::cerr << "Error loading DVD logo!" << std::endl;
    }

     float randX = getRandomNum();
     float randY = getRandomNum();

     if(randX > 6.5f) {
      randX = -randX;
     }

    if(randY > 6.5f) {
      randY = -randY;
     }

     velocity = sf::Vector2f(randX,randY);



 if (!buffer.loadFromFile("hit.wav")) {
        std::cerr << "Error loading sound file!" << std::endl;
    }
    sound.setBuffer(buffer);
  }

  void update(float windowWidth, float windowHeight) {
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    bool playSound = false;

    if(position.x  + ( size.x / 2 )> windowWidth || position.x - ( size.x /2 ) < 0) {
      velocity.x = -velocity.x;
      playSound = true;
    }
    if(position.y  + ( size.y / 2 )> windowHeight || position.y - ( size.y /2 ) < 0) {
      velocity.y = -velocity.y;
      playSound = true;
    }

  if(playSound) {
    sound.play();
  }


    shape.move(velocity);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(shape);
  }


  float getRandomNum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 9);
    float randomDecimal = static_cast<float>(distrib(gen)) / 10.0f;
    return speed + randomDecimal;
  }

  void reset() {
     shape.setSize(sf::Vector2f(startingSize.x, startingSize.y));
     shape.setOrigin(startingSize.x / 2, startingSize.y / 2);
     shape.setPosition(startingPos.x, startingPos.y);
     // shape.setFillColor(sf::Color::Green);
     shape.setTexture(&dvdTexture);
     shape.setTextureRect(sf::IntRect(0, 0, startingSize.x, startingSize.y));



  }

};
