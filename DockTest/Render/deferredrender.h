#ifndef DEFERREDRENDER_H
#define DEFERREDRENDER_H

#include "render.h"

class DeferredRender : public Renderer
{
public:
    DeferredRender();
    ~DeferredRender() override;

    void Render(Camera* camera, Scene* scene) override;

};

#endif // DEFERREDRENDER_H
