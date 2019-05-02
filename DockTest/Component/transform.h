#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component/component.h"
#include <QVector3D>
#include <QQuaternion>

class GameObject;

class Transform : public Component
{
public:
    Transform(GameObject *myGO = nullptr);
    Transform(QVector3D position, GameObject *myGO = nullptr);
    Transform(QVector3D position, QVector3D rotation, GameObject *myGO = nullptr);
    Transform(QVector3D position, QVector3D rotation, QVector3D scale, GameObject *myGO = nullptr);

    void Read(const QJsonObject &json) override;
    void Write(QJsonObject &json) const override;



public:

    QVector3D position;
    QVector3D rotation;
    QQuaternion quatRotation;
    QVector3D scale;

};

#endif // TRANSFORM_H
