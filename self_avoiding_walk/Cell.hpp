#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <string>

using std::cout;
using std::endl;

struct Wall {
  int Top = 0;
  int Right = 1;
  int Bottom = 2;
  int Left = 3;
};

class Cell {
  private:
    sf::RectangleShape cell; 
    int width; // square
    const int OUTLINE_THICKNESS = 1; // square
    const sf::Color OUTLINE_COLOR = sf::Color(252, 247, 248, 100); // square
    sf::VertexArray topLine = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray rightLine = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray bottomLine = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray leftLine = sf::VertexArray(sf::Lines, 2);
    sf::CircleShape point;
    float row;
    float col;
    Wall cellWalls;
    sf::Color cellWallColor = sf::Color::Yellow;
  public:
    sf::Vector2f position;
    bool visited = false;
    std::array<bool, 4> walls = {false, false, false, false};
    Cell(sf::Vector2f pos, int size, float rows, float cols) {
      position.x = pos.x;
      position.y = pos.y;
      width = size;
      row = rows;
      col = cols;
      cell.setPosition(pos.x * width, pos.y * width);
      cell.setSize(sf::Vector2f(width,   width ));
      cell.setFillColor(sf::Color::Transparent);
      cell.setOutlineThickness(OUTLINE_THICKNESS);
      cell.setOutlineColor(OUTLINE_COLOR);
      cell.setOrigin(sf::Vector2f(0, 0));
      

       point.setRadius(5);
       point.setOrigin(5, 5);
       point.setFillColor(sf::Color::Red);
       point.setPosition(position.x * width, position.y * width);
   }


   void draw(sf::RenderWindow& window) {
        // window.draw(cell);
        // window.draw(point);
       int x = position.x * width;
       int y = position.y * width;
      

       if(walls[cellWalls.Top]) {
         topLine[0] = sf::Vector2f(x, y);
         topLine[1] = sf::Vector2f(x + width, y);
         topLine[0].color = cellWallColor;
          topLine[1].color = cellWallColor;
         window.draw(topLine);
       }

       if(walls[cellWalls.Right]) {
         rightLine[0] = sf::Vector2f(x+ width, y);
         rightLine[1] = sf::Vector2f(x + width, y + width);
         rightLine[0].color = cellWallColor;
      rightLine[1].color = cellWallColor;
         window.draw(rightLine);

       }

       if(walls[cellWalls.Bottom]) {
        bottomLine[0] = sf::Vector2f(x + width, y + width );
        bottomLine[1] = sf::Vector2f(x , y + width);
        bottomLine[0].color = cellWallColor;
        bottomLine[1].color = cellWallColor;

             window.draw(bottomLine);
       }

       if(walls[cellWalls.Left]) {
         sf::VertexArray leftLine(sf::Lines, 2);
         leftLine[0] = sf::Vector2f(x, y + width);
         leftLine[1] = sf::Vector2f(x , y);
        leftLine[0].color = cellWallColor;
        leftLine[1].color = cellWallColor;

         window.draw(leftLine);
     }


   } 


    void highlight() {
      cell.setFillColor(sf::Color(222, 123, 112, 200));
    } 


    Cell* move(std::vector<std::unique_ptr<Cell> >& grid, sf::VertexArray& lines) {
  
      std::vector<int> neighbors;

      // Bottom Neighbor
      int top = index(position.x , position.y  -1);
      int right = index(position.x + 1, position.y );
      int bottom = index(position.x , position.y  + 1);
      int left = index(position.x  - 1 , position.y );

   

      if(top != -1 && !containsLine(lines, grid[top]->position ) && !grid[top]->visited) neighbors.push_back(top);
      if(right != -1 && !containsLine(lines, grid[right]->position) && !grid[right]->visited) neighbors.push_back(right);
      if(bottom != -1 && !containsLine(lines, grid[bottom]->position) && !grid[bottom]->visited) neighbors.push_back(bottom);
      if(left != -1 && !containsLine(lines, grid[left]->position) && !grid[left]->visited) neighbors.push_back(left);

      if(neighbors.size()) {
        int randomIdx = rand() % neighbors.size();
        // cout << neighbors[randomIdx] << endl;
        //
        //
        int chosenNeighbor = neighbors[randomIdx];
       lines.append(sf::Vertex(sf::Vector2f(grid[chosenNeighbor]->position.x * width, grid[chosenNeighbor]->position.y * width), sf::Color::Red));
       grid[chosenNeighbor]->visited = true;

    return grid[chosenNeighbor].get();
        


      }

      // remove the current point in the line vertex

      return nullptr;

    }

    bool containsLine(sf::VertexArray& lines, sf::Vector2f point) {

      for (std::size_t i = 0; i < lines.getVertexCount(); ++i) {
        if (lines[i].position == point) {
          // cout << "true" << endl;
            return true;  // The point exists in the line
        }
    }
    return false;  // The point does not exist in the line
    }

    int index(int x, int y) {
      if (x < 0 || y < 0 || x > col - 1 || y > row - 1) {
        return -1;
      }

      return x + y * col;
    }





};

