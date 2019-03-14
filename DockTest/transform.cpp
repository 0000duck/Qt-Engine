#include "transform.h"
#include<QJsonObject>

Transform::Transform(GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
{
    this->position = QPoint(0,0);
    this->rotation = QPoint(0,0);
    this->scale  = QPoint(1,1);
}

Transform::Transform(QPointF position,GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
{
    this->position =position;
    this->rotation =QPoint(0,0);
    this->scale  =QPoint(1,1);
}

Transform::Transform(QPointF position,QPointF rotation,GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = QPoint(1,1);
}

Transform::Transform(QPointF position,QPointF rotation,QPointF scale,GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Transform::Read(const QJsonObject &json)
{
    position.setX(json["positionX"].toInt());
    position.setY(json["positionY"].toInt());

    rotation.setX(json["rotationX"].toInt());
    rotation.setY(json["rotationY"].toInt());

    scale.setX(json["scaleX"].toInt());
    scale.setY(json["scaleY"].toInt());
}

void Transform::Write(QJsonObject &json) const
{
    json["name"] = "Transform";

    json["positionX"] = position.x();
    json["positionY"] = position.y();

    json["rotationX"] = rotation.x();
    json["rotationY"] = rotation.y();

    json["scaleX"] = scale.x();
    json["scaleY"] = scale.y();

}
