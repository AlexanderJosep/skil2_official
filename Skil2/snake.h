#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <iostream>
#include <string>
#include "snakegrid.h"
#include "snakewidget.h"
#include "snakethread.h"
#include "console.h"
#include "config.h"

using namespace config;

class Snake {
public:
    Snake(Console &c);
    void processSnake(Console &c); // processes the snake game
private:
    short getGridSize(Console &c, string s); // gets user input grid size
    SnakeGrid grid;
};

#endif // SNAKE_H
