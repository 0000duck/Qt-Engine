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
DEFINES +=  QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Components/component.cpp \
    Components/shaperenderer.cpp \
    Components/transform.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    Models/submesh.cpp \
    Models/vertexformat.cpp \
    Scene/gameobject.cpp \
    Scene/openglscene.cpp \
    Scene/scene.cpp \
    Widgets/hierarchywidget.cpp \
    Widgets/infowidget.cpp \
    Widgets/inspectorwidget.cpp \
    Widgets/scenewidget.cpp \
    Widgets/shaperendererwidget.cpp \
    Widgets/transformwidget.cpp \
    Models/mesh.cpp

HEADERS += \
    Components/component.h \
    Components/shaperenderer.h \
    Components/transform.h \
    Main/mainwindow.h \
    Models/submesh.h \
    Models/vertexformat.h \
    Scene/gameobject.h \
    Scene/openglscene.h \
    Scene/scene.h \
    Widgets/hierarchywidget.h \
    Widgets/infowidget.h \
    Widgets/inspectorwidget.h \
    Widgets/scenewidget.h \
    Widgets/shaperendererwidget.h \
    Widgets/transformwidget.h \
    Models/mesh.h



FORMS += \
        mainwindow.ui \
    rendering.ui \
    transformwidget.ui \
    hierarchywidget.ui \
    shaperendererwidget.ui \
    infowidget.ui

QT += opengl

CONFIG += console

LIBS += -lopengl32

RESOURCES += \
    icons.qrc

DISTFILES += \
    Shaders/forwardshading_frag.frag \
    Shaders/forwardshading_vert.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ThirdParties/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ThirdParties/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/ThirdParties/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/ThirdParties/Assimp/include
DEPENDPATH += $$PWD/ThirdParties/Assimp/include
