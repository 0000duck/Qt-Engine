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
    gameObjects.clear();

    QJsonArray goArray = json["gameObjects"].toArray();
    for(int i=0; i < goArray.size(); i++)
    {
        QJsonObject gObject = goArray[i].toObject();
        GameObject* go = new GameObject();
        go->Read(gObject);

        gameObjects.push_back(go);
    }
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
