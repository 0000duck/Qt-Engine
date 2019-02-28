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
private:
    QList<Component*> components;

};

#endif // GAMEOBJECT_H
