#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QRect>
#include <QPointF>
#include <QBrush>
#include <QFontMetrics>
#include <string>
#include "snakegrid.h"
#include "config.h"

using namespace config;

class SnakeWidget : public QWidget {
public:
    SnakeWidget(SnakeGrid *gridObject);
    void setStatus(string status);
    void setGrid(short **grid);
    bool hasStarted();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event );
private:
    SnakeGrid *gridObject;
    short **grid;
    bool started;
    string status;
};

#endif // SNAKEWIDGET_H
