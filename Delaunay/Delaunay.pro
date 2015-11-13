#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T13:33:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Delaunay
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ../DT/graph.cpp \
    graphics_view_zoom.cpp

HEADERS  += mainwindow.h \
    ../DT/components.h \
    ../DT/graph.h \
    graphics_view_zoom.h

FORMS    += mainwindow.ui
