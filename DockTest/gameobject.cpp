#include "gameobject.h"
#include "transform.h"
GameObject::GameObject()
{
    name = "GameObject";
    Transform *myTransform = new Transform(this);

    components.push_back(myTransform);
}
