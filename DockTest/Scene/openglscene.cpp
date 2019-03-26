#include "openglscene.h"
#include <iostream>
#include <QGLWidget>
#include <QOpenGLShader>

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
    glFunc = this;
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

    // VBO
    QVector3D vertices[] =
    {
        QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), // V1
        QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), // V2
        QVector3D( 0.0f,  0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)  // V3
    };
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));

    // VAO: Captures the state of VBOs
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof (QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1)),

    // Release
    vao.release();
    vbo.release();
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
    glClearDepth(1.0);
    glClearColor(0.0f, 0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Paint Triangle
    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }

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

