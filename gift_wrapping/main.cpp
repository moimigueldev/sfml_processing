#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>

sf::Vector2f windowSize = sf::Vector2f(800.0f, 500.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 10;
const int N_POINTS = 10;
const int BUFFER = 20;


sf::Font font;








int genRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}


bool compareVectors(sf::Vector2f& a, sf::Vector2f& b) {
    return a.x < b.x;
}


int main() {
  if(!font.loadFromFile("chosen_font.ttf")) { 
    std::cerr << "Errro Loading your font" << std::endl;
    return -1;
  }

  sf::Text text;
  text.setFont(font);
  text.setString("White -> currentVector to checking \nGreen -> currentVector to next vector");
  text.setCharacterSize(14); // in pixels
  text.setFillColor(sf::Color::White);
  text.setPosition(static_cast<float>(BUFFER), windowSize.y - BUFFER * 2); // x, y position on the screen

  // Points
  std::vector<sf::Vector2f> points;
  std::vector<sf::Vector2f> hull;

  for (int i = 0; i < N_POINTS; i++) {
   points.push_back(sf::Vector2f(genRandomInt(BUFFER, windowSize.x - BUFFER), genRandomInt(BUFFER, windowSize.y - BUFFER)));
  }

  // sort the points in ascending order
  std::sort(points.begin(), points.end(), compareVectors);


  // Game Defs
  sf::Vector2f& leftMost = points[0];
  sf::Vector2f& currentVector = leftMost;
  hull.push_back(currentVector);
  sf::Vector2f& nextVector = points[1];
  int index = 2;

  


  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML");
  window.setFramerateLimit(FRAMERATE);

  // Main Loop
  while(window.isOpen()) {
    sf::Event event;

    if(window.pollEvent(event)) {
    
      if(event.type == sf::Event::Closed) {
        window.close();
      }

    }

    window.clear(bgColor);


    for (int i = 0; i < N_POINTS; i++) {

      sf::CircleShape point(5);
      point.setOrigin(5, 5);

      if(points[i] == leftMost) {
        point.setFillColor(sf::Color::Green);
      } else {
        point.setFillColor(sf::Color::White);
      }
      point.setPosition(points[i].x, points[i].y);
      window.draw(point);
    }


    sf::Vector2f checking= points[index];


    // currentVector
    sf::CircleShape currentPoint(5);
    currentPoint.setOrigin(5, 5);
    currentPoint.setFillColor(sf::Color::Blue);
    currentPoint.setPosition(currentVector.x, currentVector.y);
    window.draw(currentPoint);



    // currentVector to nextVector
    sf::VertexArray currentToNext(sf::Lines, 2);
    currentToNext[0] = sf::Vector2f(currentVector.x, currentVector.y);
    currentToNext[1] = sf::Vector2f(nextVector.x, nextVector.y);
    currentToNext[0].color = sf::Color::Green;
    currentToNext[1].color = sf::Color::Green;
    window.draw(currentToNext);


    // currentVector to checking
    sf::VertexArray currentToChecking(sf::Lines, 2);
    currentToChecking[0] = sf::Vector2f(currentVector.x, currentVector.y);
    currentToChecking[1] = sf::Vector2f(checking.x, checking.y);
    currentToChecking[0].color = sf::Color(183, 183, 183);
    currentToChecking[1].color = sf::Color(183, 183, 183);
    window.draw(currentToChecking);


    window.draw(text);


    for (int i = 0; i < hull.size(); i++) {
      sf::CircleShape hullPoint(5);
      hullPoint.setOrigin(5, 5);
      hullPoint.setFillColor(sf::Color::Blue);
      hullPoint.setPosition(hull[i].x, hull[i].y);
      window.draw(hullPoint);

    }


    // vector from currentVector to nextVector 
    sf::Vector2f a  = nextVector - currentVector;

    // vector from currentVector to checking 
    sf::Vector2f b  = checking - currentVector;

    float cross = a.x * b.y - a.y * b.x;
    std::cout << cross << std::endl;


    if(cross < 0) {
      nextVector = checking;
    }

    index++;


  if(index == N_POINTS) {
    hull.push_back(nextVector);
    
    if(nextVector == leftMost) {
        std::cout << "Done " << std::endl;
        break; // Exit the loop once the hull is complete
    }

    currentVector = nextVector;
    index = 0;
    
    // Set nextVector to a point other than currentVector
    nextVector = leftMost;
}






    window.display();

  }

  return 0;
}
