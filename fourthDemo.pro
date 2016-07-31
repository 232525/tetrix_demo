#-------------------------------------------------
#
# Project created by QtCreator 2016-07-04T10:08:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fourthDemo
TEMPLATE = app


SOURCES += main.cpp\
    tetrix.cpp \
    ui_from_design.cpp \
    game_area_frame.cpp \
    next_area_frame.cpp

HEADERS  += \
    tetrix.h \
    design.h \
    ui_from_design.h \
    game_area_frame.h \
    next_area_frame.h

FORMS    +=

RESOURCES += \
    Picture.qrc
