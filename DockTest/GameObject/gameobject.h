#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component/component.h"
#include "Component/meshrenderer.h"
#include <QList>

class Transform;
class Component;

class GameObject
{
public:
    GameObject();

    void Read(const QJsonObject &json);
    void Write(QJsonObject &json) const;

    MeshRenderer* AddMesh(Shape shape);
    Transform* GetTransform();
    Component* GetComponent(Type type);


public:
    QString name;
    bool active = true;
    bool visible = true;

    QList<Component*> components;

private:

};

#endif // GAMEOBJECT_H
