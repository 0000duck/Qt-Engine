#ifndef INTERACTION_H
#define INTERACTION_H


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
