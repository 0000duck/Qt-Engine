#include "deferredrender.h"
#include "camera.h"
#include "Scene/openglscene.h"
#include "Scene/scene.h"
#include "Mesh/mesh.h"
#include "GameObject/gameobject.h"
#include "Component/transform.h"
#include "Component/meshrenderer.h"
#include "qopenglframebufferobject.h"

DeferredRender::DeferredRender()
{

}
DeferredRender::~DeferredRender()
{

}

void DeferredRender::InitProgram(int width,int height)
{

    glFuncs->glGenTextures(1,&gColor);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gColor);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);

    glFuncs->glGenTextures(1,&gDepth);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gDepth);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,nullptr);

    glFuncs->glGenFramebuffers(1,&gBuffer);
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gColor,0);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,gDepth,0);
    glFuncs->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    /*
    // Position Color
    glFuncs->glGenTextures(1,&gPosition);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gPosition);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,1024,720,0,GL_RGB,GL_FLOAT,nullptr);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gPosition,0);

    // Normal Color
    glFuncs->glGenTextures(1,&gNormal);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gNormal);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,1024,720,0,GL_RGB,GL_FLOAT,nullptr);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,gNormal,0);

    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;

    glFuncs->glDrawBuffers(2,attachments);

    glFuncs->glGenRenderbuffers(1,&gDepth);
    glFuncs->glBindRenderbuffer(GL_RENDERBUFFER,gDepth);
    glFuncs->glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,1024,720);
    glFuncs->glFramebufferRenderbuffer(GL_RENDERBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,gDepth);

    if(glFuncs->glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
       printf("Framebuffer not complete!\n");

    }
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER,0);
    */

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/cameraShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/cameraShader_tex.frag");
    program.link();
    program.bind();

    screenProgram.create();
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/screenRender.vert");
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/screenRender.frag");
    screenProgram.link();
    screenProgram.bind();

    //mesh->Update();
    program.release();
    screenProgram.release();
}
void DeferredRender::Render(Camera *camera, Scene* scene)
{
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);

    glFuncs->glClearDepth(1.0f);
    glFuncs->glClearColor(1.0f,1.0f,1.0f,1.0f);
    glFuncs->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(program.bind())
    {
        if(scene!= nullptr)
        {
            GLuint pMatrix = program.uniformLocation("projectionMat");
            glFuncs->glUniformMatrix4fv(pMatrix, 1, GL_FALSE, camera->projectionMatrix.data());

            foreach(GameObject* go, scene->gameObjects)
            {
                QMatrix4x4 model;
                model.setToIdentity();

                Transform* transform = (Transform*)go->GetComponent(Type::COMP_TRANSFORM);
                model.translate(transform->position.x(), transform->position.y(),transform->position.z());
                model.rotate(transform->quatRotation);
                model.scale(transform->scale.x(), transform->scale.y(),transform->scale.z());

                QMatrix4x4 modelView;
                modelView = camera->viewMatrix * model;
                GLuint mvMatrix = program.uniformLocation("modelViewMat");
                glFuncs->glUniformMatrix4fv(mvMatrix, 1, GL_FALSE, modelView.data());

                ((MeshRenderer*)go->GetComponent(Type::COMP_MESH_RENDERER))->Draw();
                //printf("Draw");
            }
        }
    }
    program.release();

    QOpenGLFramebufferObject::bindDefault();
    if(screenProgram.bind())
    {
        screenProgram.setUniformValue("screenTexture",0);
        glFuncs->glActiveTexture(GL_TEXTURE0);
        glFuncs->glBindTexture(GL_TEXTURE,gColor);

    }
    screenProgram.release();

}

