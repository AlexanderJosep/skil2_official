#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <iostream>
#include <string>
#include <QFrame>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QSize>
#include "snakegrid.h"
#include "snakewidget.h"
#include "snakethread.h"
#include "console.h"
#include "config.h"

using namespace config;

class Snake {
public:
    Snake(Console &c);
    int getPoints();
    short getGridSize();
private:
    short getGridSize(Console &c, string s); // gets user input grid size
    SnakeGrid grid;
};

#endif // SNAKE_H
