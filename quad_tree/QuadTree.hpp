#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "Point.hpp"

using std::cout;
using std::endl;

class Circle {
 public:
  float x, y, r, rSquared;

  Circle(float x, float y, float r) : x(x), y(y), r(r), rSquared(r * r) {}

  bool contains(const sf::Vector2f& point) const {
    float d = std::pow(point.x - x, 2) + std::pow(point.y - y, 2);
    return d <= rSquared;
  }

  bool intersects(const Circle& other) const {
    float xDist = std::abs(other.x - x);
    float yDist = std::abs(other.y - y);
    float distance = std::sqrt(xDist * xDist + yDist * yDist);
    return distance <= (r + other.r);
  }
};

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

  bool intersects(const Circle& circle) const {
    // Get the rectangle's position and size
    sf::Vector2f rectPos = shape.getPosition();
    sf::Vector2f rectSize = shape.getSize();

    // Find the closest point on the rectangle to the circle's center
    float closestX = std::max(rectPos.x - rectSize.x / 2,
                              std::min(circle.x, rectPos.x + rectSize.x / 2));
    float closestY = std::max(rectPos.y - rectSize.y / 2,
                              std::min(circle.y, rectPos.y + rectSize.y / 2));

    // Calculate the distance between the circle's center and this closest point
    float dx = circle.x - closestX;
    float dy = circle.y - closestY;
    float distanceSquared = dx * dx + dy * dy;

    // Check if the distance is less than the circle's radius
    return distanceSquared <= (circle.r * circle.r);
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
      // cout << "Inserted Point No Subdevide" << endl;
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

  std::vector<Point> query(const Circle& range,
                           std::vector<Point>& found) const {
    // if range does not intersect the boundary of this quadtree, return empty
    // vector
    if (!boundary.intersects(range)) {
      return found;
    }

    // check each point in this quadtree node to see if it's within the range
    for (const auto& point : points) {
      if (range.contains(point)) {
        found.push_back(Point(point));  // assuming Point has a constructor that
                                        // takes a sf::Vector2f
      }
    }

    // if this quadtree node has been subdivided, recursively query each
    // subdivision
    if (divided) {
      northwest->query(range, found);
      northeast->query(range, found);
      southwest->query(range, found);
      southeast->query(range, found);
    }

    return found;
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

