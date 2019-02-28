#ifndef SCENE_H
#define SCENE_H

#include <QList>

class GameObject;

class Scene
{
public:

    Scene();


public:
    QList<GameObject*> gameObjects;
};

#endif // SCENE_H
