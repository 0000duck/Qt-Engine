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
#include <QString>
#include "string.h"
DeferredRender::DeferredRender()
{   
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
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/screenRender2.vert");
    screenProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/screenRender2.frag");
    screenProgram.link();


    srand(10);
    for(int i = 0;i<10;i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        lightPos.push_back(QVector3D(xPos, yPos, zPos));
        // also calculate random color
        float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        lightColor.push_back(QVector3D(rColor, gColor, bColor));
    }
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
    printf("gNormal = %i\n",gNormal);

    glFuncs->glGenTextures(1,&gPosition);
    glFuncs->glBindTexture(GL_TEXTURE_2D,gPosition);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glFuncs->glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glFuncs->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    printf("gPosition = %i\n",gPosition);

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
    printf("gBuffer = %i\n",gBuffer);
    printf("-----------\n");

    attachments[0] = GL_COLOR_ATTACHMENT0;
    attachments[1] = GL_COLOR_ATTACHMENT1;
    attachments[2] = GL_COLOR_ATTACHMENT2;
    glFuncs->glDrawBuffers(3, attachments);

    GLenum status = glFuncs->glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
    printf("Framebuffer OK: GL_FRAMEBUFFER_OK\n"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    printf("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    printf("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    printf("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    printf("Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n"); break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
    printf("Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED\n"); break;
    default:
    printf("Framebuffer ERROR: Unknown ERROR\n");
    }
}

void DeferredRender::DeleteBuffers()
{
    glFuncs->glDeleteTextures(1, &gColor);
    glFuncs->glDeleteTextures(1, &gNormal);
    glFuncs->glDeleteTextures(1, &gPosition);
    glFuncs->glDeleteTextures(1, &gDepth);

    glFuncs->glDeleteFramebuffers(1, &gBuffer);
}

void DeferredRender::Render(Camera *camera, Scene* scene)
{
    glFuncs->glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

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

                glFuncs->glActiveTexture(GL_TEXTURE0);

                ((MeshRenderer*)go->GetComponent(Type::COMP_MESH_RENDERER))->Draw();
            }
        }
    }
    program.release();

    QOpenGLFramebufferObject::bindDefault();

    if(screenProgram.bind())
    {       
        screenProgram.setUniformValue(screenProgram.uniformLocation("gAlbedo"), 0);
        screenProgram.setUniformValue(screenProgram.uniformLocation("gNormal"), 1);
        screenProgram.setUniformValue(screenProgram.uniformLocation("gPosition"), 2);


        screenProgram.setUniformValue(screenProgram.uniformLocation("renderView"), renderView);

        glFuncs->glActiveTexture(GL_TEXTURE0);
        glFuncs->glBindTexture(GL_TEXTURE_2D, gColor);

        glFuncs->glActiveTexture(GL_TEXTURE1);
        glFuncs->glBindTexture(GL_TEXTURE_2D, gNormal);

        glFuncs->glActiveTexture(GL_TEXTURE2);
        glFuncs->glBindTexture(GL_TEXTURE_2D, gPosition);

        for(int i = 0;i<lightPos.size();i++)
        {

             glFuncs->glUniform3fv(glFuncs->glGetUniformLocation(screenProgram.programId(), ("lights["+QString::number(i)+"].Position").toStdString().c_str()),1,&lightPos[i][0]);
             glFuncs->glUniform3fv(glFuncs->glGetUniformLocation(screenProgram.programId(),("lights["+QString::number(i)+"].Color").toStdString().c_str()),1,&lightColor[i][0]);

             float constant = 1.0f;
             float linear = 0.7f;
             float quadratic = 1.8f;
             glFuncs->glUniform1f(glFuncs->glGetUniformLocation(screenProgram.programId(),("lights["+QString::number(i)+"].Linear").toStdString().c_str()),linear);
             glFuncs->glUniform1f(glFuncs->glGetUniformLocation(screenProgram.programId(),("lights["+QString::number(i)+"].Linear").toStdString().c_str()),quadratic);

        }
        glFuncs->glUniform3fv(glFuncs->glGetUniformLocation(screenProgram.programId(), "viewPos"),1, &camera->position[0]);

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

