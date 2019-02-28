#include "component.h"
#include "gameobject.h"

Component::Component(GameObject* myGO)
{
    this->myGO = myGO;
}
