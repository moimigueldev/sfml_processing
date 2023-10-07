#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Rectangle {
 private:
 public:
  sf::CircleShape center;
  sf::RectangleShape shape;
  Rectangle(sf::Vector2f pos, sf::Vector2f size) {
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::Transparent);
    shape.setSize(size);
    shape.setPosition(pos);
    shape.setOrigin(size.x / 2, size.y / 2);

    center.setRadius(9);
    center.setOrigin(9, 9);
    center.setOutlineColor(sf::Color::Green);
    center.setPosition(shape.getPosition().x, shape.getPosition().y);
  }

  bool contains(sf::Vector2f point) {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    return (point.x >= pos.x - size.x / 2 && point.x <= pos.x + size.x / 2 &&
            point.y >= pos.y - size.y / 2 && point.y <= pos.y + size.y / 2);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(center);
  }
};

class QuadTree {
 private:
  int capacity;
  Rectangle boundary;
  std::vector<sf::Vector2f> points;
  bool divided = false;
  QuadTree* northwest = nullptr;
  QuadTree* northeast = nullptr;
  QuadTree* southwest = nullptr;
  QuadTree* southeast = nullptr;

 public:
  QuadTree(Rectangle bound, int cap) : boundary(bound) { capacity = cap; }

  bool insert(sf::Vector2f point) {
    // cout << "Does it contain ?? " << boundary.contains(point) << endl;
    if (!boundary.contains(point)) {
      return false;
    }

    if (points.size() < capacity) {
      points.push_back(point);
      cout << "Inserted Point No Subdevide" << endl;
      return true;
    }

    if (!divided) {
      subdivide();
    }

    if (northwest && northwest->insert(point)) return true;
    if (northeast && northeast->insert(point)) return true;
    if (southwest && southwest->insert(point)) return true;
    if (southeast && southeast->insert(point)) return true;
    return false;
  }

  ~QuadTree() {
    delete northwest;
    delete northeast;
    delete southwest;
    delete southeast;
  }

  void subdivide() {
    sf::Vector2f size = boundary.shape.getSize();
    sf::Vector2f pos = boundary.shape.getPosition();

    Rectangle nw =
        Rectangle(sf::Vector2f(pos.x - size.x / 4, pos.y - size.y / 4),
                  sf::Vector2f(size.x / 2, size.y / 2));

    Rectangle ne =
        Rectangle(sf::Vector2f(pos.x + size.x / 4, pos.y - size.y / 4),
                  sf::Vector2f(size.x / 2, size.y / 2));

    Rectangle sw =
        Rectangle(sf::Vector2f(pos.x - size.x / 4, pos.y + size.y / 4),
                  sf::Vector2f(size.x / 2, size.y / 2));

    Rectangle se =
        Rectangle(sf::Vector2f(pos.x + size.x / 4, pos.y + size.y / 4),
                  sf::Vector2f(size.x / 2, size.y / 2));

    northwest = new QuadTree(nw, capacity);
    northeast = new QuadTree(ne, capacity);
    southwest = new QuadTree(sw, capacity);
    southeast = new QuadTree(se, capacity);

    divided = true;
  }

  void draw(sf::RenderWindow& window) {
    window.draw(boundary.shape);
    // window.draw(boundary.center);
    if (divided) {
      northwest->draw(window);
      northeast->draw(window);
      southwest->draw(window);
      southeast->draw(window);
    }
  }
};

