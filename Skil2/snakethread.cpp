#include "snakethread.h"

SnakeThread::SnakeThread(SnakeGrid *grid, SnakeWidget *widget, Console *c, QMainWindow *window) {
    this -> grid = grid;
    this -> widget = widget;
    this -> c = c;
    this -> window = window;
}

void SnakeThread::run() {
    msleep(1250);
    while( window -> isVisible()) {
        if(!(grid -> update((*c)))) {
            if(grid -> hasWon()) {
                 grid -> print((*c));
                 c -> println("You WIN. Points: " + to_string((*grid).getSnakeSize() - 3));
            } else {
                grid -> pushLostSnake();
                c -> println("You lose. Points: " + to_string((*grid).getSnakeSize() - 3));
            }
            widget -> setGrid((*grid).getGrid());
       //     emit widget -> repaint();
            widget -> update();
            break;
        }
        widget -> setGrid((*grid).getGrid());
      //  emit widget -> repaint();
        widget -> update();
        msleep(SNAKE_SLEEP_TIME);
    }
}
