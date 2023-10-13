#pragma once

#include <SFML/Graphics.hpp>

#include "Particle.hpp"
#include "Utility.hpp"

namespace EventUtils {
void handleCloseEvent(sf::RenderWindow& window) {
  sf::Event event;

  if (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

void handleMousePressEvents(sf::RenderWindow& window,
                            std::vector<Particle>& particles) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    float offsetX = Utility::genRandomInt(-10, 10);
    float offsetY = Utility::genRandomInt(-10, 10);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float mouseX = static_cast<float>(mousePos.x) + offsetX;
    float mouseY = static_cast<float>(mousePos.y) + offsetY;
    particles.push_back(Particle(sf::Vector2f(mouseX, mouseY)));
  }
}

}  // namespace EventUtils
