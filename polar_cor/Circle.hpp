#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <SFML/Audio.hpp>

class Circle {
  private:
    int RADIUS;
    const std::string soundFile = "mech_keyboard.mp3";
    const int OUTLINE_THICKNESS = 5;
    const int CORD_RADIUS = 10;
    sf::Color cordColor;
    sf::CircleShape shape;
    sf::CircleShape center;
    sf::CircleShape cord; float radian = 0.0f;
    bool increasing = false;
    float radianSpeed;
    float opacity = 255.0f;

    sf::SoundBuffer buffer;
    sf::Sound sound;


  public:
   Circle(sf::Vector2f windowSize, int setRadius, float speed) {
    RADIUS = setRadius;
    radianSpeed = speed;
    cordColor = sf::Color(genRandomNum(0, 255), genRandomNum(0, 255), genRandomNum(0, 255));
    shape.setRadius(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setPosition(windowSize.x / 2, windowSize.y);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(OUTLINE_THICKNESS); // Set border width
    shape.setOutlineColor(sf::Color::Transparent);


    center.setRadius(5);
    center.setOrigin(5, 5);
    center.setPosition(shape.getPosition().x, shape.getPosition().y);
    center.setFillColor(sf::Color::Blue);

    cord.setRadius(CORD_RADIUS);
    cord.setOrigin(CORD_RADIUS, CORD_RADIUS);
    cord.setPosition(shape.getPosition().x + RADIUS * cos(radian), shape.getPosition().y + RADIUS * sin(radian));
    cord.setFillColor(cordColor);
    // cord.setOutlineThickness(OUTLINE_THICKNESS);
    // cord.setOutlineColor(cordColor);
    
  
    if(!buffer.loadFromFile(soundFile)) {
      std::cerr << "Errro Loading sound from file!" << std::endl;
    }
    sound.setBuffer(buffer);


   }



   void update() {
    cord.setPosition(shape.getPosition().x + RADIUS * cos(radian), shape.getPosition().y + RADIUS * sin(radian));


    setShapeOpacity(cord, opacity);

    float degrees = (radian * 180.0f) / M_PI;

    if(degrees <= -180.0f) {
      increasing = true;
      opacity = 255.0f;
      sound.play();
    } else if(degrees >= 0.0f) {
      opacity = 255.0f;
      increasing = false;
      sound.play();
    }

    if(increasing) {
        radian += radianSpeed;
    } else {
        radian -= radianSpeed;
    }


    opacity -= 1.0f;




}



   void draw(sf::RenderWindow& window) {
    window.draw(shape);
    // window.draw(center);
    window.draw(cord);
   }

   void setShapeOpacity(sf::Shape& shape, sf::Uint8 opacity) {
    sf::Color fillColor = shape.getFillColor();
    fillColor.a = opacity;
    shape.setFillColor(fillColor);

    sf::Color outlineColor = shape.getOutlineColor();
    outlineColor.a = opacity;
    shape.setOutlineColor(outlineColor);
   }

  int genRandomNum(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);

  }


};

