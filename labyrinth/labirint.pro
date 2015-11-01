#-------------------------------------------------
#
# Project created by QtCreator 2015-10-31T01:11:07
#
#-------------------------------------------------

QT       += core gui winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS += "img/logo.ico"

TARGET = labirint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filenameedit.cpp \
    pixmapwidget.cpp \
    labyrinth.cpp \
    graph.cpp \
    labyrinthparser.cpp \
    labyrinthwidget.cpp \
    labyrinthstatementswidget.cpp

HEADERS  += mainwindow.h \
    filenameedit.h \
    pixmapwidget.h \
    labyrinth.h \
    graph.h \
    types.h \
    labyrinthparser.h \
    labyrinthwidget.h \
    labyrinthstatementswidget.h

RESOURCES += \
    res.qrc
