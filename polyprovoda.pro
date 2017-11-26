#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T16:02:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polyprovoda
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/qwt-qt4
LIBS += -L/usr/lib -lqwt-qt4
