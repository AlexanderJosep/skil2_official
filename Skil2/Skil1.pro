QT += core
QT += core sql
QT -= gui

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
    computermanager.cpp

HEADERS += \
    person.h \
    personmanager.h \
    console.h \
    storage.h \
    snake.h \
    snakegrid.h \
    computer.h \
    computermanager.h

DISTFILES += \
    persons.txt
