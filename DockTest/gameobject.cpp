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


Transform* GameObject::GetTransform()
{
    for(int i =0;i<components.size();i++)
    {
        if(components[i]->type== Type::COMP_TRANSFORM)
        {
            return (Transform*)components[i];
        }
    }
    return nullptr;
}

Component* GameObject::GetComponent(Type type)
{
    for(int i =0;i<components.size();i++)
    {
        if(components[i]->type== type)
        {
            return components[i];
        }
    }
    return nullptr;
}
