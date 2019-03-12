#include "gameobject.h"
#include "transform.h"
#include "shaperenderer.h"
GameObject::GameObject()
{
    name = "GameObject";
    Transform *myTransform = new Transform(this);
    ShapeRenderer *myShapeRenderer = new ShapeRenderer(this);

    components.push_back(myTransform);
    components.push_back(myShapeRenderer);

}
