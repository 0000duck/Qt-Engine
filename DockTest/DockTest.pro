#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:15:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DockTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    openglscene.cpp \
    inspectorwidget.cpp \
    transformwidget.cpp \
    hierarchywidget.cpp \
    positioncommand.cpp \
    rotationcommand.cpp \
    scalecommand.cpp \
    shaperendererwidget.cpp

HEADERS += \
        mainwindow.h \
    openglscene.h \
    inspectorwidget.h \
    transformwidget.h \
    hierarchywidget.h \
    scalecommand.h \
    rotationcommand.h \
    positioncommand.h \
    shaperendererwidget.h

FORMS += \
        mainwindow.ui \
    rendering.ui \
    transformwidget.ui \
    hierarchywidget.ui \
    shaperendererwidget.ui

QT += opengl

CONFIG += console

LIBS += -lopengl32

RESOURCES += \
    icons.qrc
