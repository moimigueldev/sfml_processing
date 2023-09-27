#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include <random>


using std::cout;
using std::endl;

class Boid {
  private:
    sf::VertexArray boid;
    sf::Vector2f velocity;
    sf::Vector2f centerPos;
    sf::Vector2f acc = sf::Vector2f(0.0f, 0.0f);
    float terminalVelocity = 20.0f;
    float angle;
    float length = 30.0f; // Length from the center to the beak
    float halfBase = 10.0f; // Half of the base width of the triangle
    int neighborhoodRadius = 100;
    sf::Color color;

  public:
   Boid(sf::Vector2f center) {
     boid = sf::VertexArray(sf::Triangles, 3);
     color = sf::Color(genRandomInt(0, 255), genRandomInt(0, 255), genRandomInt(0, 255));
     centerPos = center;

    
     do {
        velocity.x = 6.0f * genRandomFloat(-1.0f, 1.0f);
    } while (std::abs(velocity.x) < 2.0f);  // Ensure minimum threshold

    do {
        velocity.y = 6.0f * genRandomFloat(-1.0f, 1.0f);
    } while (std::abs(velocity.y) < 2.0f);  // Ensure minimum threshold


     // Calculate the able based on velcity (radians)
     angle = atan2(velocity.y, velocity.x);

     // tip of the traingle;
     sf::Vector2f pos1 = center + sf::Vector2f(length * cos(angle), length * sin(angle));
     sf::Vector2f pos2 = center + sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));
     sf::Vector2f pos3 = center - sf::Vector2f(-halfBase * sin(angle), halfBase * cos(angle));

     boid[0].position = pos1;
     boid[0].color = color;

     boid[1].position = pos2;
     boid[1].color = color;

     boid[2].position = pos3;
     boid[2].color = color;


     

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
   
  float genRandomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);

    return distrib(gen);

  }

  static int genRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);

  }

  void highlightRadius(sf::RenderWindow& window) {

    float centroidX = (boid[0].position.x + boid[1].position.x + boid[2].position.x) / 3;
    float centroidY = (boid[0].position.y + boid[1].position.y + boid[2].position.y) / 3;

    sf::CircleShape radiusCircle(neighborhoodRadius);
    radiusCircle.setRadius(neighborhoodRadius);
    radiusCircle.setPosition(centroidX - neighborhoodRadius, centroidY - neighborhoodRadius);
    radiusCircle.setFillColor(sf::Color( 52, 127, 196, 50 ));
    window.draw(radiusCircle);
  }
  
  void seperation(const std::vector<std::unique_ptr<Boid> >& boids, int index) {


    std::vector<Boid*> boidsInNeighborhood;
    sf::Vector2f weightedAvoidenceVector;

    for (int i = 0; i < boids.size(); i++) {
      if(i == index) continue;
      sf::Vector2f distance = getCentroid() - boids[i]->getCentroid();
      float magnitude = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
      if(magnitude <= neighborhoodRadius) {
        boidsInNeighborhood.push_back(boids[i].get());
      }
    }


    for (int i = 0; i < boidsInNeighborhood.size(); i++) {
      sf::Vector2f vectorToNeighbor = getCentroid() - boidsInNeighborhood[i]->getCentroid();
      float inverseDistance;
      float magnitude = sqrt(pow(vectorToNeighbor.x, 2) + pow(vectorToNeighbor.y, 2));
      sf::Vector2f normalizedVector;

      if(magnitude <= 0) {
        normalizedVector = vectorToNeighbor;
      } else {
        normalizedVector.x = vectorToNeighbor.x / magnitude;
        normalizedVector.y = vectorToNeighbor.y / magnitude;

      }

      if (magnitude <= 0) {
        inverseDistance = 1000.0f;
      } else {
        inverseDistance = 1 / magnitude;
      }


      weightedAvoidenceVector.x += normalizedVector.x * inverseDistance;
      weightedAvoidenceVector.y += normalizedVector.y * inverseDistance;

    }
      // cout << weightedAvoidenceVector.x << " " << weightedAvoidenceVector.y << endl;

      weightedAvoidenceVector *= static_cast<float>( boidsInNeighborhood.size() ); // Scale by a factor of 5

    acc += weightedAvoidenceVector;


  }


  sf::Vector2f getCentroid() {
    float centroidX = (boid[0].position.x + boid[1].position.x + boid[2].position.x) / 3;
    float centroidY = (boid[0].position.y + boid[1].position.y + boid[2].position.y) / 3;

    return sf::Vector2f(centroidX, centroidY);
    
  }


};

