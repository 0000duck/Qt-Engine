#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Component/component.h"

class GameObject;
class Mesh;

enum Shape
{
    NONE = -1,
    SPHERE,
    CUBE,
    PLANE,
    CUSTOM,
};

class MeshRenderer : public Component
{
public:
    MeshRenderer(GameObject* myGO = nullptr, Shape shape = Shape::NONE);
    void Draw();

private:
    Mesh* mesh = nullptr;

public:
    Shape shape = Shape::NONE;
};

#endif // MESHRENDERER_H
