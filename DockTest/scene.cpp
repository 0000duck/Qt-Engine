#include "scene.h"
#include "gameobject.h"

#include <QList>
#include <QJsonArray>
#include <QJsonObject>


Scene::Scene()
{

}

void Scene::Read(const QJsonObject &json)
{

}

void Scene::Write(QJsonObject &json) const
{
    QJsonArray goArray;
    foreach (GameObject* go, gameObjects)
    {
        QJsonObject gObject;
        go->Write(gObject);
        goArray.append(gObject);
    }
    json["gameObjects"] = goArray;
}
