#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
#include <QWidget>

enum Type
{
    COMP_INFO,
    COMP_TRANSFORM,
    COMP_MESH_RENDERER,

    NO_TYPE
};
class Component
{
public:
    Component(GameObject* myGO,Type type=Type::NO_TYPE);

public:
    Type type;

private:
    GameObject* myGO;
};

#endif // COMPONENT_H
