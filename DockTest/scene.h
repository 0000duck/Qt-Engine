#ifndef SCENE_H
#define SCENE_H

#include <QList>

class GameObject;

class Scene
{
public:

    Scene();
    void Read(const QJsonObject &json);
    void Write(QJsonObject &json) const;

public:
    QList<GameObject*> gameObjects;
};

#endif // SCENE_H
