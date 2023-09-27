#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <cmath>
#include <random>


using std::cout;
using std::endl;

class Boid {
  private:
    sf::VertexArray boid;
    sf::Vector2f velocity;
    sf::Vector2f acc = sf::Vector2f(0.0f, 0.0f);
    float terminalVelocity = 20.0f;
    float angle;
    float length = 30.0f; // Length from the center to the beak
    float halfBase = 10.0f; // Half of the base width of the triangle

  public:
   Boid(sf::Vector2f center) {
     boid = sf::VertexArray(sf::Triangles, 3);

    
     do {
        velocity.x = 6.0f * genRandomNum(-1.0f, 1.0f);
    } while (std::abs(velocity.x) < 2.0f);  // Ensure minimum threshold

    do {
        velocity.y = 6.0f * genRandomNum(-1.0f, 1.0f);
    } while (std::abs(velocity.y) < 2.0f);  // Ensure minimum threshold


     // Calculate the able based on velcity (radians)
     angle = atan2(velocity.y, velocity.x);

     // tip of the traingle;
     sf::Vector2f pos1 = center + sf::Vector2f(length * cos(angle), length * sin(angle));
     sf::Vector2f pos2 = center + sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));
     sf::Vector2f pos3 = center - sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));

     boid[0].position = pos1;
     boid[0].color = sf::Color::Red;

     boid[1].position = pos2;
     boid[1].color = sf::Color::Red;

     boid[2].position = pos3;
     boid[2].color = sf::Color::Red;


     cout << velocity.x << " " << velocity.y << endl;
     

   }


   void update(sf::Vector2f windowSize) {

     velocity += acc;

     if( velocity.x > terminalVelocity) {
        velocity.x = terminalVelocity;
      }

     if( velocity.y > terminalVelocity) {
        velocity.y = terminalVelocity;
      }


    float desiredAngle = atan2(velocity.y, velocity.x);
    float angleDifference = desiredAngle - angle;

    // Check if the angle difference is above a threshold (e.g., 0.01 radians)
    if (std::abs(angleDifference) > 0.01) {
        angle = desiredAngle;
        rotateTo();
    }

    




     boid[0].position += velocity;
     boid[1].position += velocity;
     boid[2].position += velocity;





     // Check if the boid's head goes out of bounds
    if (boid[0].position.y < 0) {
        float offset = 0 - boid[0].position.y;
        for (int i = 0; i < 3; i++) {
            boid[i].position.y += windowSize.y + offset;
        }
    }
    if (boid[0].position.y > windowSize.y) {
        float offset = boid[0].position.y - windowSize.y;
        for (int i = 0; i < 3; i++) {
            boid[i].position.y -= windowSize.y + offset;
        }
    }
    if (boid[0].position.x > windowSize.x) {
        float offset = boid[0].position.x - windowSize.x;
        for (int i = 0; i < 3; i++) {
            boid[i].position.x -= windowSize.x + offset;
        }
    }
    if (boid[0].position.x < 0) {
        float offset = 0 - boid[0].position.x;
        for (int i = 0; i < 3; i++) {
            boid[i].position.x += windowSize.x + offset;
        }
    }



     acc *= 0.0f;

   }


   void draw(sf::RenderWindow& window) {
    window.draw(boid);
   }


   void rotateTo() {
    sf::Vector2f center = boid[0].position;

    for (int i = 0; i < 3; i++) {
      float x = boid[i].position.x - center.x;
      float y = boid[i].position.y - center.y;


      boid[i].position.x = center.x + x * cos(angle) - y * sin(angle);
      boid[i].position.y = center.y + x * sin(angle) + y * cos(angle);
      
    }
   }
   
  float genRandomNum(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);

    return distrib(gen);

  }

};

