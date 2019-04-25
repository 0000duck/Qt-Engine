#ifndef FORWARDRENDER_H
#define FORWARDRENDER_H

#include "render.h"

class Camera;
class GameObject;
class Scene;

class ForwardRender : public Renderer
{
public:
    ForwardRender();
    ~ForwardRender() override;
    void InitProgram();
    void Render(Camera* camera, Scene* scene) override;

private:



};

#endif // FORWARDRENDER_H
