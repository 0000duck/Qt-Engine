#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"
#include <QList>
class Transform;
class Component;

class GameObject
{
public:
    GameObject();
    void Read(const QJsonObject &json);
    void Write(QJsonObject &json) const;
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
