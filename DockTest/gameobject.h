#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QList>
#include "component.h"
class GameObject
{
public:
    GameObject();
private:

    QList<Component*> components;

};

#endif // GAMEOBJECT_H
