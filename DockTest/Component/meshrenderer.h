#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Component/component.h"

class GameObject;
class Mesh;

enum Shape
{
    SPHERE = 0,
    CUBE,
    PLANE,
    CUSTOM
};

class MeshRenderer : public Component
{
public:
    MeshRenderer(GameObject* myGO = nullptr);

    Mesh* mesh = nullptr;

};

#endif // MESHRENDERER_H
