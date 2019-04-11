#ifndef FORWARDRENDER_H
#define FORWARDRENDER_H

#include "render.h"

class Camera;
class ForwardRender : public Renderer
{
public:
    ForwardRender();
    ~ForwardRender() override;
    void InitProgram();
    void Render(Camera* camera) override;

private:

};

#endif // FORWARDRENDER_H
