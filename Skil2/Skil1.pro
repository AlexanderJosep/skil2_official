QT += core
QT += core sql
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Skil1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    person.cpp \
    console.cpp \
    storage.cpp \
    snake.cpp \
    snakegrid.cpp \
    computer.cpp \
    snakewidget.cpp \
    snakethread.cpp \
    entity.cpp \
    entitymanager.cpp

HEADERS += \
    person.h \
    console.h \
    storage.h \
    snake.h \
    snakegrid.h \
    computer.h \
    snakewidget.h \
    snakethread.h \
    config.h \
    entity.h \
    entitymanager.h

DISTFILES +=
