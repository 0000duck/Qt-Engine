#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"
#include <QList>

class GameObject
{
public:
    GameObject();

public:
    QString name;
    QList<Component*> components;

private:

};

#endif // GAMEOBJECT_H
