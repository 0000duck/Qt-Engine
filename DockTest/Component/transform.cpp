#include "transform.h"
#include<QJsonObject>

Transform::Transform(GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
{
    this->position = QVector3D(0,0,0);
    this->rotation = QVector3D(0,0,0);
    this->scale  = QVector3D(1,1,1);
}

Transform::Transform(QVector3D position, GameObject *myGO):Component(myGO, Type::COMP_TRANSFORM)
{
    this->position = position;
    this->rotation = QVector3D(0,0,0);
    this->scale  = QVector3D(1,1,1);
}

Transform::Transform(QVector3D position,QVector3D rotation,GameObject *myGO):Component(myGO, Type::COMP_TRANSFORM)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = QVector3D(1,1,1);
}

Transform::Transform(QVector3D position, QVector3D rotation, QVector3D scale,GameObject *myGO):Component(myGO,Type::COMP_TRANSFORM)
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
