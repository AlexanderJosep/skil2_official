#include "SnakeGrid.h"

using namespace std;

static int getRanInt(int size) {
    return rand() % size;
}

SnakeGrid::SnakeGrid() {
    candyX = -1;
    candyY = -1;
}

void SnakeGrid::initialize() {
    for(int i = 0; i < 3; i++) {
        snakeX.push_back(0);
    }
    for(int i = 0; i < 3; i++) {
        snakeY.push_back(2 - i);
    }
    pushSnake();
    setRandomCandy();
    pushCandy();
    direction = 3;
    canUpdateDir = true;
    lostSnakeX = -1;
    lostSnakeY = -1;
}

void SnakeGrid::setDirection(int dir) {
    // cannot go to the opposite direction, just the sides
    if(!canUpdateDir || (dir == 0 && direction == 2) || (dir == 2 && direction == 0) || (dir == 1 && direction == 3) || (dir == 3 && direction == 1)) {
        return;
    }
    canUpdateDir = false;
    direction = dir;
}

bool SnakeGrid::update(Console &c) {
    resetGrid();
    if(!updateSnake(c, direction)) {
        return false;
    }
    canUpdateDir = true;
    pushSnake();
    pushCandy();
    return true;
}

void SnakeGrid::pushLostSnake() {
    resetGrid();
    for(unsigned int i = 1; i < snakeX.size(); i++) {
        grid[snakeX[i]][snakeY[i]] = 1;
    }
    lostSnakeX = snakeX[0] + 1;
    lostSnakeY = snakeY[0] + 1;
    pushCandy();
}

bool SnakeGrid::hasWon() {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            if(grid[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

bool SnakeGrid::updateSnake(Console &, int dir) {
    int offX = dir == 0 ? -1 : (dir == 2 ? 1 : 0);
    int offY = dir == 1 ? -1 : (dir == 3 ? 1 : 0);
    for(unsigned int i = 1; i < snakeX.size(); i++) {
        if(snakeX[0] + offX == snakeX[i] && snakeY[0] + offY == snakeY[i]) { // collided with itself
            return false;
        }
    }
    int oldX = snakeX[snakeX.size() - 1];
    int oldY = snakeY[snakeY.size() - 1];
    for(unsigned int i = snakeX.size() - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    snakeX[0] = snakeX[0] + offX;
    snakeY[0] = snakeY[0] + offY;
    if(snakeX[0] == candyX && snakeY[0] == candyY) { // eat candy
        snakeX.push_back(oldX);
        snakeY.push_back(oldY);
        pushSnake();
        if(hasWon()) {
            return false;
        }
        setRandomCandy();
    }
    return !(snakeX[0] < 0 || snakeX[0] >= gridSize || snakeY[0] < 0 || snakeY[0] >= gridSize);
}

void SnakeGrid::pushSnake() {
    for(unsigned int i = 0; i < snakeX.size(); i++) {
        grid[snakeX[i]][snakeY[i]] = 1;
    }
}

void SnakeGrid::pushCandy() {
    grid[candyX][candyY] = 2;
}

void SnakeGrid::setRandomCandy() {
    do {
        candyX = getRanInt(gridSize);
        candyY = getRanInt(gridSize);
    } while(grid[candyX][candyY] == 1);
}

void SnakeGrid::setGrid(int size) {
    grid = new short*[size];
    for(int i = 0; i < size; i++) {
        grid[i] = new short[size];
        for(int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
    gridSize = size;
}

void SnakeGrid::resetGrid() {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            grid[i][j] = 0;
        }
    }
}

int SnakeGrid::getSnakeSize() {
    return snakeX.size();
}

short** SnakeGrid::getGrid() {
    return grid;
}

short SnakeGrid::getGridSize() {
    return gridSize;
}

short SnakeGrid::getLostSnakeX() {
    return lostSnakeX;
}

short SnakeGrid::getLostSnakeY() {
    return lostSnakeY;
}
