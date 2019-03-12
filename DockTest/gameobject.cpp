#include "gameobject.h"
#include "transform.h"

#include <QJsonArray>
#include <QJsonObject>

#include "shaperenderer.h"

GameObject::GameObject()
{
    name = "GameObject";
    Transform *myTransform = new Transform(this);
    ShapeRenderer *myShapeRenderer = new ShapeRenderer(this);

    components.push_back(myTransform);
    components.push_back(myShapeRenderer);
}

void GameObject::Read(const QJsonObject &json)
{
    // Read Base Info
    name = json["name"].toString();
    active = json["isActive"].toBool();
    visible = json["isVisible"].toBool();

    // Read Components
    components.clear();

    QJsonArray compArray = json["components"].toArray();
    for(int i=0; i < compArray.size(); i++)
    {
        QJsonObject compObject = compArray[i].toObject();
        components[i]->Read(compObject);
    }
}

void GameObject::Write(QJsonObject &json) const
{
    // Save Components Info
    QJsonArray compArray;
    foreach (Component* comp, components)
    {
        QJsonObject compObject;
        comp->Write(compObject);
        compArray.append(compObject);
    }
    json["components"] = compArray;

    // Save Base Info
    json["name"] = name;
    json["isActive"] = active;
    json["isVisible"] = visible;
}
