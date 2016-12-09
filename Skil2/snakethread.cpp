#include "snakethread.h"

SnakeThread::SnakeThread(SnakeGrid *grid, SnakeWidget *widget, Console *c, QMainWindow *window) {
    this -> grid = grid;
    this -> widget = widget;
    this -> c = c;
    this -> window = window;
}

void SnakeThread::run() {
    while(window -> isVisible()) { // we don't wanna keep running if the window has closed
        if(!widget -> hasStarted()) {
            msleep(25);
            continue;
        }
        if(!(grid -> update((*c)))) {
            if(grid -> hasWon()) {
                 widget -> setStatus("You WIN!");
            } else {
                grid -> pushLostSnake();
                widget -> setStatus("You lose.");
            }
            widget -> setGrid(grid -> getGrid());
            widget -> update();
            break;
        }
        widget -> setGrid(grid -> getGrid());
        widget -> update();
        msleep(SNAKE_SLEEP_TIME);
    }
}
