#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    Component(GameObject* myGO);
private:
    GameObject* myGO;
};

#endif // COMPONENT_H
