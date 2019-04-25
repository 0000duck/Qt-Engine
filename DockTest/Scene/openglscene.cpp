#include "openglscene.h"
#include <iostream>
#include <QGLWidget>
#include <QOpenGLShader>
#include "Mesh/mesh.h"
#include "QMatrix4x4"
#include "Render/forwardrender.h"
#include "Render/camera.h"
#include "Input/input.h"
#include "Input/interation.h"
QOpenGLFunctions_3_3_Core *glFuncs;


OpenGLScene::OpenGLScene(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setMouseTracking(true);
    connect(&timer,SIGNAL(timeout()),this,SLOT(Frame()));
    if(format().swapInterval()==-1)
    {
        timer.setInterval(17);
    }
    else {
        timer.setInterval(0);
    }
    timer.start();
    setMinimumSize(QSize(256,256));
}

OpenGLScene::~OpenGLScene()
{
    makeCurrent();
    finalizeGL();
}

void OpenGLScene::initializeGL()
{
    makeCurrent();
    input = new Input();
    interaction = new Interaction();
    renderer = new ForwardRender();
    camera = new Camera();
    camera->SetViewport(this->width(),this->height());
    interaction->input = input;
    interaction->mainCamera = camera;

    glFuncs = this;
    initializeOpenGLFunctions();

    // Depth Test
    if(enableZtest)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        if(enableZwrite)
            glDepthMask(GL_TRUE);
        else
            glDepthMask(GL_FALSE);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    renderer->InitProgram();

    // Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));
}

void OpenGLScene::resizeGL(int width, int height)
{
    makeCurrent();

    glViewport(0,0,width,height);
    camera->SetViewport(width, height);

    // Resize textures;
}

void OpenGLScene::paintGL()
{
    makeCurrent();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->PrepareMatrices();

    if(scene!=nullptr)
    {
        renderer->Render(camera, scene);
    }
}

void OpenGLScene::TakeScreenShot()
{
   image = GetScreenShot();
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

bool OpenGLScene::GetScene(Scene *scenePointer)
{
    if(scenePointer == nullptr)
        return false;

    scene = scenePointer;
    return true;
}
void OpenGLScene::Frame()
{
    bool needUpdate = interaction->Update();
    if(needUpdate)
    {
        update();
    }

    input->PostUpdate();
}

void OpenGLScene::keyPressEvent(QKeyEvent* event)
{
    printf("KeyDown\n");
    input->KeyDownEvent(event);
}
void OpenGLScene::keyReleaseEvent(QKeyEvent* event)
{
    printf("KeyUp\n");
    input->KeyUpEvent(event);

}
void OpenGLScene::mousePressEvent(QMouseEvent* event)
{
    printf("MouseDown\n");
    input->MouseButtonDownEvent(event);
    setFocus();
}
void OpenGLScene::mouseReleaseEvent(QMouseEvent* event)
{

    printf("MouseUp\n");
    input->MouseButtonUpEvent(event);

}
void OpenGLScene::mouseMoveEvent(QMouseEvent* event)
{
    input->MouseMoveEvent(event);
}
