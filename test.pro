#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T16:15:13
#
#-------------------------------------------------

QT       += core gui
CONFIG +=CONSOLE

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GPXByteBuffer.cpp

HEADERS  += mainwindow.h \
    GPXByteBuffer.h

FORMS    += mainwindow.ui
