#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
#include <QWidget>

enum Type
{
    COMP_TRANSFORM,
    COMP_MESH_RENDERER,

    NO_TYPE
};

class Component
{
public:
    Component(GameObject* myGO,Type type=Type::NO_TYPE);
    virtual ~Component();

    virtual void Read(const QJsonObject &json);
    virtual void Write(QJsonObject &json) const;

public:
    Type type;

private:
    GameObject* myGO;
};

#endif // COMPONENT_H
