#ifndef DEFERREDRENDER_H
#define DEFERREDRENDER_H

#include "render.h"
#include <QOpenGLTexture>

class DeferredRender : public Renderer
{
public:
    DeferredRender();
    ~DeferredRender() override;
    void InitProgram();
    void Resize(int width,int height);
    void DeleteBuffers();
    void Render(Camera* camera, Scene* scene) override;
    void RenderQuad();

public:

    unsigned int gBuffer;

   // unsigned int gPosition;
    //unsigned int gNormal;
    unsigned int gColor;
    unsigned int gDepth;

    unsigned int attachments[2];

    unsigned int quadVAO = 0;
    unsigned int quadVBO;

    QOpenGLTexture* texture;
};

#endif // DEFERREDRENDER_H
