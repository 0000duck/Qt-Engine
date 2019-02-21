#include "openglscene.h"

OpenGLScene::OpenGLScene(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void OpenGLScene::initializeGL()
{

}

void OpenGLScene::resizeGL(int width, int height)
{

}

void OpenGLScene::paintGL()
{
    glClearColor(0.5f, 0.7f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
