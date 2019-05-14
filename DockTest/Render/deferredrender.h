#ifndef DEFERREDRENDER_H
#define DEFERREDRENDER_H

#include "render.h"

class DeferredRender : public Renderer
{
public:
    DeferredRender();
    ~DeferredRender() override;
    void InitProgram(int width,int height);

    void Render(Camera* camera, Scene* scene) override;


public:

    unsigned int gBuffer;

   // unsigned int gPosition;
    //unsigned int gNormal;
    unsigned int gColor;
    unsigned int gDepth;

    unsigned int attachments[2];

};

#endif // DEFERREDRENDER_H
