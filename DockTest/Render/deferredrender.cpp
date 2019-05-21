#include "deferredrender.h"
#include "camera.h"
#include "Scene/openglscene.h"
#include "Scene/scene.h"
#include "Mesh/mesh.h"
#include "GameObject/gameobject.h"
#include "Component/transform.h"
#include "Component/meshrenderer.h"
#include "qopenglframebufferobject.h"
#include <QOpenGLTexture>

DeferredRender::DeferredRender()
{
    texture = new QOpenGLTexture(QImage("Textures/Flowers.png"));
}
DeferredRender::~DeferredRender()
{

}

void DeferredRender::InitProgram()
{
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/cameraShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/cameraShader_tex.frag");
    program.link();

    screenProgram.create();
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/screenRender.vert");
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/screenRender.frag");
    screenProgram.link();
}

void DeferredRender::Resize(int width,int height)
{
    // ----- TEST 1 ------
    printf("\nResize-----------\n");
    glFuncs->glGenTextures(1,&gColor);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gColor);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    printf("gColor = %i\n",gColor);

    glFuncs->glGenTextures(1,&gNormal);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gNormal);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    printf("gColor = %i\n",gNormal);

    glFuncs->glGenTextures(1,&gPosition);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gPosition);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    printf("gColor = %i\n",gPosition);

    glFuncs->glGenTextures(1,&gDepth);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gDepth);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,nullptr);
    printf("gDepth = %i\n",gDepth);

    glFuncs->glGenFramebuffers(1,&gBuffer);
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gColor,0);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,gNormal,0);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT2,GL_TEXTURE_2D,gPosition,0);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,gDepth,0);

    //glFuncs->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;
    attachments[2] = GL_COLOR_ATTACHMENT2;
    glFuncs->glDrawBuffers(3, attachments);


    printf("gBuffer = %i\n",gBuffer);
    printf("-----------\n");

    //------ TEST 1 -----

    /*// TEST 2

    // Buffer
    glFuncs->glGenFramebuffers(1, &gBuffer);
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // Position
    glFuncs->glGenTextures(1,&gPosition);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gPosition);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,1024,720,0,GL_RGB,GL_FLOAT,nullptr);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,gPosition,0);

    // Normals
    glFuncs->glGenTextures(1,&gNormal);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gNormal);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,1024,720,0,GL_RGB,GL_FLOAT,nullptr);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,gNormal,0);

    // Textures
    glFuncs->glGenTextures(1, &gColor);
    glFuncs->glBindTexture(GL_TEXTURE_2D, gColor);
    glFuncs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFuncs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColor, 0);

    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;
    attachments[2] = GL_COLOR_ATTACHMENT2;
    glFuncs->glDrawBuffers(3, attachments);


     // TEST 2 */
}

void DeferredRender::DeleteBuffers()
{
    glFuncs->glDeleteTextures(1,&gColor);
    glFuncs->glDeleteTextures(1,&gDepth);
    glFuncs->glDeleteFramebuffers(1,&gBuffer);
}

void DeferredRender::Render(Camera *camera, Scene* scene)
{
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER,gBuffer);

    glFuncs->glClearDepth(1.0f);
    glFuncs->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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

                Transform* transform = go->GetTransform();
                model.translate(transform->position.x(), transform->position.y(),transform->position.z());
                model.rotate(transform->quatRotation);
                model.scale(transform->scale.x(), transform->scale.y(),transform->scale.z());

                QMatrix4x4 modelView;
                modelView = camera->viewMatrix * model;
                GLuint mvMatrix = program.uniformLocation("modelViewMat");
                glFuncs->glUniformMatrix4fv(mvMatrix, 1, GL_FALSE, modelView.data());

                ((MeshRenderer*)go->GetComponent(Type::COMP_MESH_RENDERER))->Draw();
            }
        }
    }
    program.release();

    QOpenGLFramebufferObject::bindDefault();

    if(screenProgram.bind())
    {       
        screenProgram.setUniformValue("screenTexture", 0);
        glFuncs->glActiveTexture(GL_TEXTURE0);
        glFuncs->glBindTexture(GL_TEXTURE_2D, gColor);
        //glFuncs->glActiveTexture(GL_TEXTURE0);
        //glFuncs->glBindTexture(GL_TEXTURE_2D, gNormal);
        //glFuncs->glActiveTexture(GL_TEXTURE2);
        //glFuncs->glBindTexture(GL_TEXTURE_2D, gPosition);
        RenderQuad();
    }

    screenProgram.release();


}

void DeferredRender::RenderQuad()
{
    if (quadVAO == 0)
     {
         float quadVertices[] = {
             // Positions               // texCoords       // Color
             -1.0f,  1.0f, 0.0f,        0.0f, 1.0f,        1.0, 0.0, 0.0,
             -1.0f, -1.0f, 0.0f,        0.0f, 0.0f,        0.0, 1.0, 0.0,
              1.0f,  1.0f, 0.0f,        1.0f, 1.0f,        0.0, 0.0, 0.0,
              1.0f, -1.0f, 0.0f,        1.0f, 0.0f,        1.0, 1.0, 1.0
         };
         // setup plane VAO
         glFuncs->glGenVertexArrays(1, &quadVAO);
         glFuncs->glGenBuffers(1, &quadVBO);
         glFuncs->glBindVertexArray(quadVAO);
         glFuncs->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
         glFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
         glFuncs->glEnableVertexAttribArray(0);
         glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
         glFuncs->glEnableVertexAttribArray(1);
         glFuncs->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
         glFuncs->glEnableVertexAttribArray(2);
         glFuncs->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
     }

    glFuncs->glBindVertexArray(quadVAO);
    glFuncs->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFuncs->glBindVertexArray(0);
    glFuncs->glBindTexture(GL_TEXTURE_2D, 0);

}

