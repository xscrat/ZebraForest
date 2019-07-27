#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T10:03:24
#
#-------------------------------------------------

QT       += core gui webkitwidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZebraForest
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    codeeditor.cpp \
    graphiceditor.cpp \
    highlighter.cpp \
    settingwindow.cpp \
    connectconditionitem.cpp \
    spritedetailpanel.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    graphiceditor.h \
    highlighter.h \
    settingwindow.h \
    connectconditionitem.h \
    spritedetailpanel.h

FORMS    += mainwindow.ui \
    settingwindow.ui \
    connectconditionitem.ui \
    spritedetailpanel.ui

RESOURCES += \
    resource.qrc
