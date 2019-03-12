#include "gameobject.h"
#include "transform.h"

#include <QJsonArray>
#include <QJsonObject>

GameObject::GameObject()
{
    name = "GameObject";
    Transform *myTransform = new Transform(this);

    components.push_back(myTransform);
}

void GameObject::Read(const QJsonObject &json)
{

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
