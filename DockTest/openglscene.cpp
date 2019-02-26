#include "openglscene.h"

OpenGLScene::OpenGLScene(QWidget *parent) :
    QOpenGLWidget(parent)
{

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
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLScene::finalizeGL()
{
    printf("finalizeGL()");
}
