#include "snake.h"
using namespace std;

Snake::Snake(Console &c) {
    short gridSize = getGridSize(c, "Grid size(10-30): ");
    grid.setGrid(gridSize);
    grid.initialize();
    //start the snake frame
    int argc = 0;
    char* argv[] = {};
    QApplication application(argc, &argv[0]);

    QMainWindow *window = new QMainWindow();
    window -> setWindowTitle(QString::fromUtf8("Snake"));
    window -> resize((gridSize + 2) * (SNAKE_CELL_SIZE + 2), (gridSize + 2) * (SNAKE_CELL_SIZE + 2) + SNAKE_BAR_OFFSET);
    QSize size = QSize((gridSize + 2) * (SNAKE_CELL_SIZE + 2), (gridSize + 2) * (SNAKE_CELL_SIZE + 2) + SNAKE_BAR_OFFSET);
    window -> setMinimumSize(size);
    window -> setMaximumSize(size);

    SnakeWidget *widget = new SnakeWidget(&grid);
    widget -> setGrid(grid.getGrid());
    window -> setCentralWidget(widget);
    window -> show();
    window -> setFocus();
    window -> activateWindow();
    window -> raise();
    widget -> setFocus();

    //start the snake thread -> handles all the snake processing
    SnakeThread *thread = new SnakeThread(&grid, widget, &c, window);
    thread -> start();

    application.exec();

}

short Snake::getGridSize(Console &c, string s) {
    short in;
    while(true) {
        cout << s;
        cin >> in;
        if(in < 10 || in > 30) {
            c.println("Please select a grid size between 3 - 50.");
            c.clearBuffer();
            continue;
        }
        break;
    }
    return in;
}
