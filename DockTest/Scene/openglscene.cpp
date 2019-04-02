#include "openglscene.h"
#include <iostream>
#include <QGLWidget>
#include <QOpenGLShader>
#include "Mesh/mesh.h"

QOpenGLFunctions_3_3_Core *glFuncs;
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
    makeCurrent();
    mesh = new Mesh();
    mesh->LoadModel("Models/sponza.obj");
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

    // Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/forwardshading_vert.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/forwardshading_frag.frag");
    program.link();
    program.bind();

    if(mesh!=nullptr)
    {
       mesh->Update();
    }
    program.release();


    // Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

}

void OpenGLScene::resizeGL(int width, int height)
{
    // Resize textures
}

void OpenGLScene::paintGL()
{
    makeCurrent();

    glClearDepth(1.0);
    glClearColor(1.0f, 0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mesh!=nullptr)
    {
       //mesh->Update();
        if(program.bind())
        {

        mesh->Draw();
        program.release();

        }
    }
    // Paint Triangle
    /*
    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }
    */

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
bool OpenGLScene::GetScene(Scene *scenePointer)
{
    if(scenePointer == nullptr)
        return false;

    scene = scenePointer;
    return true;
}

