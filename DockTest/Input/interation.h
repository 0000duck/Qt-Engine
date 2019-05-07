#ifndef INTERACTION_H
#define INTERACTION_H

#include "QVector3D"
class GameObject;
class Camera;
class Input;
class Interaction
{
public:
    Interaction();

    bool Update();

private:
    bool Idle();
    bool Navigation();


    bool RayCast(const QVector3D &positionWorldSpace, const QVector3D & directionWorldSpace,GameObject** hit);

public:
    Camera* mainCamera = nullptr;
    Input* input = nullptr;
private:
    enum State
    {
        IDLE,
        NAVIGATION,

    };
    State state = State::IDLE;
};

#endif // INTERATION_H
