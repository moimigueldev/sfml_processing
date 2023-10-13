#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Circle.hpp"
#include "Particle.hpp"
#include "Rectangle.hpp"

class QuadTree {
 private:
  int capacity;
  Rectangle boundary;
  std::vector<std::reference_wrapper<Particle> > particles;
  QuadTree* northwest = nullptr;
  QuadTree* northeast = nullptr;
  QuadTree* southwest = nullptr;
  QuadTree* southeast = nullptr;

 public:
  bool divided = false;
  QuadTree(Rectangle bound, int cap) : boundary(bound) { capacity = cap; }

  bool insert(Particle& point) {
    if (!boundary.contains(point)) {
      return false;
    }

    if (particles.size() < capacity) {
      particles.push_back(point);
      return true;
    }

    if (!divided) {
      subdivide();
    }

    if (northwest->insert(point)) return true;
    if (northeast->insert(point)) return true;
    if (southwest->insert(point)) return true;
    if (southeast->insert(point)) return true;

    return false;
  }

  void subdivide() {
    sf::Vector2f pos = boundary.shape.getPosition();
    sf::Vector2f size = boundary.shape.getSize();

    Rectangle nw =
        Rectangle(sf::Vector2f(pos.x - size.x / 4.0f, pos.y - size.y / 4.0f),
                  size / 2.0f);
    Rectangle ne =
        Rectangle(sf::Vector2f(pos.x + size.x / 4.0f, pos.y - size.y / 4.0f),
                  size / 2.0f);
    Rectangle sw =
        Rectangle(sf::Vector2f(pos.x - size.x / 4.0f, pos.y + size.y / 4.0f),
                  size / 2.0f);
    Rectangle se =
        Rectangle(sf::Vector2f(pos.x + size.x / 4.0f, pos.y + size.y / 4.0f),
                  size / 2.0f);

    northwest = new QuadTree(nw, capacity);
    northeast = new QuadTree(ne, capacity);
    southwest = new QuadTree(sw, capacity);
    southeast = new QuadTree(se, capacity);

    divided = true;
  }

  ~QuadTree() {
    delete northwest;
    delete northeast;
    delete southwest;
    delete southeast;
  }

  void query(const Circle& range, Particle& centerParticle,
             std::vector<std::reference_wrapper<Particle> >& found) const {
    if (!boundary.intersects(range)) {
      return;
    }

    for (const auto& particleRef : particles) {
      Particle& particle = particleRef.get();
      if (&particle != &centerParticle && range.contains(particle)) {
        found.push_back(particleRef);
      }
    }

    if (divided) {
      northwest->query(range, centerParticle, found);
      northeast->query(range, centerParticle, found);
      southwest->query(range, centerParticle, found);
      southeast->query(range, centerParticle, found);
    }
  }

  void draw(sf::RenderWindow& window) {
    boundary.draw(window);

    if (divided) {
      northwest->draw(window);
      northeast->draw(window);
      southwest->draw(window);
      southeast->draw(window);
    }
  }
};

