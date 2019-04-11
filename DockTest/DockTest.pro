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
    Component/component.cpp \
    Component/infowidget.cpp \
    Component/shaperenderer.cpp \
    Component/transform.cpp \
    ComponentWidget/hierarchywidget.cpp \
    ComponentWidget/inspectorwidget.cpp \
    ComponentWidget/meshrendererwidget.cpp \
    ComponentWidget/shaperendererwidget.cpp \
    ComponentWidget/transformwidget.cpp \
    GameObject/gameobject.cpp \
    Input/input.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    Mesh/mesh.cpp \
    Mesh/submesh.cpp \
    Mesh/vertexformat.cpp \
    Render/camera.cpp \
    Render/deferredrender.cpp \
    Render/forwardrender.cpp \
    Render/render.cpp \
    Scene/openglscene.cpp \
    Scene/scene.cpp \
    SceneWidget/scenewidget.cpp


HEADERS += \
    Component/component.h \
    Component/infowidget.h \
    Component/shaperenderer.h \
    Component/transform.h \
    ComponentWidget/hierarchywidget.h \
    ComponentWidget/inspectorwidget.h \
    ComponentWidget/meshrendererwidget.h \
    ComponentWidget/shaperendererwidget.h \
    ComponentWidget/transformwidget.h \
    GameObject/gameobject.h \
    Input/input.h \
    Main/mainwindow.h \
    Mesh/mesh.h \
    Mesh/submesh.h \
    Mesh/vertexformat.h \
    Render/camera.h \
    Render/deferredrender.h \
    Render/forwardrender.h \
    Render/render.h \
    Scene/openglscene.h \
    Scene/scene.h \
    SceneWidget/scenewidget.h



FORMS += \
        mainwindow.ui \
    rendering.ui \
    transformwidget.ui \
    hierarchywidget.ui \
    shaperendererwidget.ui \
    infowidget.ui \
    ComponentWidget/meshrendererwidget.ui

QT += opengl

CONFIG += console

LIBS += -lopengl32

RESOURCES += \
    icons.qrc

DISTFILES += \
    Shaders/forwardshading_frag.frag \
    Shaders/forwardshading_vert.vert \
    Shaders/cameraShader.frag \
    Shaders/cameraShader.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ExternalLibrary/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ExternalLibrary/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/ExternalLibrary/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/ExternalLibrary/Assimp/include
DEPENDPATH += $$PWD/ExternalLibrary/Assimp/include
