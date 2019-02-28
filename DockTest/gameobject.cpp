#include "gameobject.h"
#include "transform.h"
GameObject::GameObject()
{
    Transform *myTransform = new Transform(this);

    components.push_back(myTransform);
}
