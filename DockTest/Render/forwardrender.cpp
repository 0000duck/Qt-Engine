#include "forwardrender.h"
#include "camera.h"
#include "Scene/openglscene.h"
#include "Mesh/mesh.h"
ForwardRender::ForwardRender()
{

}
ForwardRender::~ForwardRender()
{

}
void ForwardRender::InitProgram()
{
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/cameraShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/cameraShader.frag");
    program.link();
    program.bind();


    mesh->Update();
    program.release();

}
void ForwardRender::Render(Camera *camera)
{

    QMatrix4x4 model;
    model.setToIdentity();

    QMatrix4x4 modelView;
    modelView = camera->viewMatrix * model;
    GLuint mvMatrix = program.uniformLocation("modelViewMat");

    glFuncs->glUniformMatrix4fv(mvMatrix, 1, GL_FALSE, modelView.data());

    GLuint pMatrix = program.uniformLocation("projectionMat");

    glFuncs->glUniformMatrix4fv(pMatrix, 1, GL_FALSE, camera->projectionMatrix.data());


    if(program.bind())
    {
        mesh->Draw();
        program.release();
    }

}
