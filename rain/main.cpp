#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "RainDrop.hpp"

sf::Vector2i windowSize = sf::Vector2i(1000, 800);
sf::Color bgColor = sf::Color(0);
const int FRAMERATE = 30;
const int N_RAINDROP = 500;
const int N_STARS = 100;  // Number of stars

void setupRain(std::vector<RainDrop>& rainList) {
  rainList.clear();
  for (int i = 0; i < N_RAINDROP; i++) {
    int randX = RainDrop::genRandomInt(0, windowSize.x);
    int randY = RainDrop::genRandomInt(0, windowSize.y);
    RainDrop newRainDrop = RainDrop(
        sf::Vector2f(static_cast<float>(randX), static_cast<float>(randY)));
    rainList.push_back(newRainDrop);
  }
}

void addWind(int direction, std::vector<RainDrop>& rain, sf::Vector2f force) {
  float degreesOfRotation = 0.5 * direction;
  for (int i = 0; i < N_RAINDROP; i++) {
    rain[i].rotate(degreesOfRotation);
    rain[i].addAcc(sf::Vector2f(force.x, force.y));
  }
}

void setupStars(std::vector<sf::CircleShape>& stars) {
  stars.clear();
  for (int i = 0; i < N_STARS; ++i) {
    sf::CircleShape star;
    star.setFillColor(sf::Color::White);
    star.setRadius(
        static_cast<float>(rand() % 3 + 1));  // Star size between 1 and 3
    star.setPosition(static_cast<float>(rand() % windowSize.x),
                     static_cast<float>(rand() % windowSize.y));
    stars.push_back(star);
  }
}

int main() {
  std::vector<RainDrop> rain;
  setupRain(rain);

  std::vector<sf::CircleShape> stars;
  setupStars(stars);

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while (window.isOpen()) {
    sf::Event event;

    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Left:
            addWind(1, rain, sf::Vector2f(-2, 0));
            break;
          case sf::Keyboard::Right:
            addWind(-1, rain, sf::Vector2f(2, 0));
            break;
          default:
            setupRain(rain);
            break;
        }
      }
    }

    window.clear(bgColor);

    // Draw Stars
    for (auto& star : stars) {
      window.draw(star);
    }

    // Draw Raindrops
    for (int i = 0; i < N_RAINDROP; i++) {
      rain[i].update(static_cast<sf::Vector2f>(windowSize));
      rain[i].draw(window);
    }

    window.display();
  }

  return 0;
}

