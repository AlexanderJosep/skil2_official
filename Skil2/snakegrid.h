#ifndef SNAKEGRID_H
#define SNAKEGRID_H
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include "console.h"
#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

class SnakeGrid {
public:
    SnakeGrid();
    void initialize(); // initializes the grid
    void setDirection(int dir); // sets the snakes direction
    bool update(Console &c); // updates the snake with the next direction
    void pushLostSnake(); // pushes a lost snake, everything but the part that's off the map/loses
    bool hasWon(); // check if the player won
    short** getGrid(); // returns the grid data
    short getGridSize(); // gets the grid size
    short getLostSnakeX(); // gets the cell X where the snake lost
    short getLostSnakeY(); // gets the cell Y where the snake lost
    int getSnakeSize(); // gets snake size for calculating points
    void setGrid(int size); // sets grid size
    void print(Console &c); // prints the snake game out
private:
    bool updateSnake(Console &c, int dir); // updates the snakes position and checks for collision and walking out of grid
    void pushSnake(); // pushes the snake onto the grid
    void pushCandy(); // pushes the candy onto the grid
    void setRandomCandy(); // sets candy to a random pos
    void resetGrid(); // resets the grid
    void setColor(unsigned short col); // sets console color
    short **grid;
    short gridSize;
    short candyX;
    short candyY;
    short lostSnakeX;
    short lostSnakeY;
    vector<int> snakeX;
    vector<int> snakeY;
    int direction;
    bool canUpdateDir;
};

#endif // SNAKEGRID_H
