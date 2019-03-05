#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QPointF>
class GameObject;

class Transform : public Component
{
public:
    Transform(GameObject *myGO = nullptr);
    Transform(QPointF position,GameObject *myGO = nullptr);
    Transform(QPointF position,QPointF rotation,GameObject *myGO = nullptr);
    Transform(QPointF position,QPointF rotation,QPointF scale,GameObject *myGO = nullptr);

public:
QPointF position;
QPointF rotation;
QPointF scale;

};

#endif // TRANSFORM_H
