#include "component.h"
#include "gameobject.h"

Component::Component(GameObject* myGO,Type type)
{
    this->myGO = myGO;
    this->type=type;
}

Component::~Component()
{

}

void Component::Read(const QJsonObject &json)
{

}
void Component::Write(QJsonObject &json) const
{

}
