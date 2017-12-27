#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T10:18:34
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DragAndDropPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
