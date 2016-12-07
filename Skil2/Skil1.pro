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
    personmanager.cpp \
    console.cpp \
    storage.cpp \
    snake.cpp \
    snakegrid.cpp \
    computer.cpp \
    computermanager.cpp \
    snakewidget.cpp \
    snakethread.cpp

HEADERS += \
    person.h \
    personmanager.h \
    console.h \
    storage.h \
    snake.h \
    snakegrid.h \
    computer.h \
    computermanager.h \
    snakewidget.h \
    snakethread.h \
    config.h

DISTFILES += \
    persons.txt
