#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <cmath>

class Boid {
  private:
    sf::VertexArray boid;
    sf::Vector2f velocity = sf::Vector2f(-9.0f, 0.0f);
    sf::Vector2f acc = sf::Vector2f(0.0f, 0.0f);
    float terminalVelocity = 20.0f;
    float angle;
    float length = 30.0f; // Length from the center to the beak
    float halfBase = 10.0f; // Half of the base width of the triangle

  public:
   Boid(sf::Vector2f center) {

     angle = atan2(velocity.y, velocity.x);

     boid = sf::VertexArray(sf::Triangles, 3);


     sf::Vector2f pos1 = center +  sf::Vector2f(length * cos(angle), length * sin(angle));
     sf::Vector2f pos2 = center + sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));
     sf::Vector2f pos3 = center - sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));

     boid[0].position = pos1;
     boid[0].color = sf::Color::Red;

     boid[1].position = pos2;
     boid[1].color = sf::Color::Red;

     boid[2].position = pos3;
     boid[2].color = sf::Color::Red;
     

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





     if(boid[0].position.y < 0 ) {
      boid[0].position = sf::Vector2f(boid[0].position.x, windowSize.y -30);
      boid[1].position = sf::Vector2f(boid[1].position.x, windowSize.y );
      boid[2].position = sf::Vector2f(boid[2].position.x, windowSize.y );
     }
     if(boid[0].position.y > windowSize.y ) {
      boid[0].position = sf::Vector2f(boid[0].position.x, 30);
      boid[1].position = sf::Vector2f(boid[1].position.x, 0 );
      boid[2].position = sf::Vector2f(boid[2].position.x, 0 );
     }
     if(boid[0].position.x > windowSize.x ) {
      boid[0].position.x = 30;
      boid[1].position.x = 0;
      boid[2].position.x = 0;
     }
     if(boid[0].position.x <  0 ) {
      boid[0].position.x = windowSize.x - 30;
      boid[1].position.x = windowSize.x;
      boid[2].position.x = windowSize.x;
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

};

