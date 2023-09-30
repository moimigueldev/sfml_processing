#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

  class Ball  {
    private:
      sf::Vector2f acc;
      const float MAX_VEL = 40.0f;
      const float BALL_SPEED = 6.0f;
    public:
      sf::Vector2f vel;
      sf::CircleShape ball;
      const int RADIUS = 10;
      Ball (sf::Vector2f position) {

        vel.x = getRandomFloat(BALL_SPEED, BALL_SPEED + 0.9f);
        vel.y = getRandomFloat(BALL_SPEED, BALL_SPEED + 0.9f);
        vel.y *= -1;


        int xDirection = genRandomInt(0, 1);
        int yDirection = genRandomInt(0, 1);


        if(xDirection == 1) {
          vel.x *= -1;
        }

        // if(yDirection == 1) {
          // vel.y *= -1;
        // }



        ball.setRadius(RADIUS);
        ball.setOrigin(RADIUS, RADIUS);
        ball.setFillColor(sf::Color::Red);
        ball.setPosition(position.x, position.y);

      }


      void update(sf::Vector2f windowSize) {
        
      
        vel += acc;


      if(ball.getPosition().x - RADIUS < 0 ) {
        vel.x *= -1;
      }

      if(ball.getPosition().x + RADIUS > windowSize.x) {
        vel.x *= -1;
      }
      if(ball.getPosition().y - RADIUS < 0) {
        vel.y *= -1;
      }
        


        ball.move(vel);


        acc *= 0.9f;

      }

      void draw(sf::RenderWindow& window) {
        window.draw(ball);
      }


      static float getRandomFloat(float min, float max) {
        static std::random_device rd; 
        static std::mt19937 rng(rd()); 
        std::uniform_real_distribution<float> uni(min, max);
        return uni(rng);
      }


       static int genRandomInt(int min, int max) {
        static std::random_device rd; 
        static std::mt19937 rng(rd()); 
        std::uniform_int_distribution<> uni(min, max);
        return uni(rng);
      }


};

