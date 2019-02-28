#include "openglscene.h"
#include <iostream>
#include <QGLWidget>

OpenGLScene::OpenGLScene(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
}
OpenGLScene::~OpenGLScene()
{
    makeCurrent();
    finalizeGL();
}




void OpenGLScene::initializeGL()
{
    initializeOpenGLFunctions();

    // Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));
}

void OpenGLScene::resizeGL(int width, int height)
{
    // Resize textures
}

void OpenGLScene::paintGL()
{

    glClearColor(0.5f, 0.7f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void OpenGLScene::TakeScreenShot()
{
   image= GetScreenShot();
   image.save("Escriptori.png");
}
QImage OpenGLScene::GetScreenShot()
{
    std::cout<<"GetScreenShot"<<std::endl;

    makeCurrent();
    return grabFramebuffer();
}
void OpenGLScene::finalizeGL()
{
    std::cout<<"finalizeGL()"<<std::endl;
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


