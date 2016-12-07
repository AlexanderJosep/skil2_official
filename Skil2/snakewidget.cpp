#include "snakewidget.h"

SnakeWidget::SnakeWidget(SnakeGrid *gridObject) {
    this -> gridObject = gridObject;
    grid = new short*[(*gridObject).getGridSize()];
    for(int i = 0; i < (*gridObject).getGridSize(); i++) {
        grid[i] = new short[(*gridObject).getGridSize()];
        for(int j = 0; j < (*gridObject).getGridSize(); j++) {
            grid[i][j] = 0;
        }
    }
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    for(int i = 1; i < gridObject -> getGridSize() + 1; i++) {
        for(int j = 1; j < gridObject -> getGridSize() + 1; j++) {
            if(grid[i - 1][j - 1] == 0) {
                painter.drawRect(QRect(j * (SNAKE_CELL_SIZE + 2) + 2, i * (SNAKE_CELL_SIZE + 2) + 2, SNAKE_CELL_SIZE, SNAKE_CELL_SIZE));
            } else if(grid[i - 1][j - 1] == 1) {
                painter.drawEllipse(QPointF(j * (SNAKE_CELL_SIZE + 2) + 2 + SNAKE_CELL_SIZE / 2 , i * (SNAKE_CELL_SIZE + 2) + 2 + SNAKE_CELL_SIZE / 2), SNAKE_CELL_SIZE / 2, SNAKE_CELL_SIZE / 2);
            } else {
                painter.fillRect(QRect(j * (SNAKE_CELL_SIZE + 2) + 2, i * (SNAKE_CELL_SIZE + 2) + 2, SNAKE_CELL_SIZE, SNAKE_CELL_SIZE), QBrush(QColor(128, 128, 255, 128)));
            }
        }
    }
    if(gridObject -> getLostSnakeX() >= 0 && gridObject -> getLostSnakeY() >= 0) {
        int i = gridObject -> getLostSnakeX();
        int j = gridObject -> getLostSnakeY();
        painter.drawEllipse(QPointF(j * (SNAKE_CELL_SIZE + 2) + 2 + SNAKE_CELL_SIZE / 2 , i * (SNAKE_CELL_SIZE + 2) + 2 + SNAKE_CELL_SIZE / 2), SNAKE_CELL_SIZE / 2, SNAKE_CELL_SIZE / 2);
    }
    painter.end();
}

void SnakeWidget::mousePressEvent(QMouseEvent * event) {
    setFocus();
}

void SnakeWidget::keyPressEvent(QKeyEvent* event){
    int key = event -> key();
    int dir = (key == 87 || key == 16777235) ? 0 : ((key == 65 || key == 16777234) ? 1 :
              ((key == 83 || key == 16777237) ? 2 : ((key == 68 || key == 16777236) ? 3 : -1)));
    if(dir >= 0) {
        (*gridObject).setDirection(dir);
    }
}

void SnakeWidget::setGrid(short **grid) {
    this -> grid = new short*[(*gridObject).getGridSize()];
    for(int i = 0; i < (*gridObject).getGridSize(); i++) {
        this -> grid[i] = new short[(*gridObject).getGridSize()];
        for(int j = 0; j < (*gridObject).getGridSize(); j++) {
            this -> grid[i][j] = grid[i][j];
        }
    }
}
