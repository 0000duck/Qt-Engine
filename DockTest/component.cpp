#include "component.h"
#include "gameobject.h"

Component::Component(GameObject* myGO,Type type)
{
    this->myGO = myGO;
    this->type=type;
}

