#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include <cmath>

sf::Vector2f windowSize = sf::Vector2f(1000.0f, 800.0f);
sf::Color bgColor = sf::Color(68, 70, 83);
const int FRAMERATE = 60;
const int N_NODES = 30;
const int NODE_RADIUS = 10;





int genRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(min, max);

  return distrib(gen);
}


bool compareVectors(sf::Vector2f& a, sf::Vector2f& b) {
  return a.x < b.x;
}


bool notInVisited(sf::Vector2f& node, sf::VertexArray path) {

  for (int i = 0; i < path.getVertexCount(); i++) {
   if(path[i].position == node) return false; 
  }


  return true;
}


int main() {

  // All nodes
  sf::CircleShape point(NODE_RADIUS);
  point.setOrigin(NODE_RADIUS, NODE_RADIUS);
  


  std::vector<sf::Vector2f>  nodes;
  std::vector<sf::Vector2f*>  nodesVisited;


  for (int i = 0; i < N_NODES; i++) {
    nodes.push_back(sf::Vector2f(sf::Vector2f(genRandomInt(0, static_cast<int>(windowSize.x)),genRandomInt(0, static_cast<int>(windowSize.y)))));
  }

  std::sort(nodes.begin(), nodes.end(), compareVectors);


  sf::VertexArray path(sf::LineStrip);
  sf::Vector2f& startingNode = nodes[0];
  sf::Vector2f& endingNode = nodes[nodes.size() - 1];
  sf::Vector2f& nextNode = nodes[0];
  sf::Vector2f currentNode = nodes[0];
  auto cost = std::numeric_limits<float>::max();
  int lowestCostIndex;
  int index = 1;
  path.append(startingNode);


  // Sort the nodes

  sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "A * Algorithm (random points)");
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

    for (int i = 0; i < N_NODES; i++) {
      point.setPosition(nodes[i].x, nodes[i].y);

      
      if(nodes[i] == startingNode) {
        point.setFillColor(sf::Color::Green);
      }
      else if (nodes[i] == endingNode) {
        point.setFillColor(sf::Color::Red);
      }
      else {
        point.setFillColor(sf::Color::White);
      }
    
      window.draw(point);
    }


    window.draw(path);


    // Check nodes
    sf::Vector2f& checking = nodes[index];
    if(currentNode == endingNode) {
      
      std::cout << "DONE: "  << std::endl;
    }
    if(checking != currentNode && notInVisited(nodes[index], path)) {

      // Cost of currentNode and  startingNode
      float g = sqrt(pow(checking.x - currentNode.x , 2) + pow(checking.y - currentNode.y , 2));

      // Cost of currentNode to endingNode
      float h = sqrt(pow(checking.x - endingNode.x , 2) + pow(checking.y - endingNode.y , 2));


      // total cost
      float f = g + h;


      if(cost == 0.0f) {

        cost = f;
        lowestCostIndex = index;
      }


      if(f < cost) {
        cost = f;
        lowestCostIndex = index;
      }


    }

    index++;


    if(index == nodes.size()) {
      std::cout << "Done: " << cost << std::endl;
      cost = std::numeric_limits<float>::max();
      path.append(nodes[lowestCostIndex]);
      currentNode = nodes[lowestCostIndex];
      lowestCostIndex = 0;
      index = 0;
    }



    window.display();

  }

  return 0;
}
