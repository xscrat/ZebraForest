#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T10:03:24
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZebraForest
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    graphiceditor.cpp \
    highlighter.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    graphiceditor.h \
    highlighter.h

FORMS    += mainwindow.ui
