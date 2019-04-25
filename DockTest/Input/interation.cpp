#include "interation.h"
#include "Input/input.h"
#include "Render/camera.h"
#include "QtMath"
Interaction::Interaction()
{

}


bool Interaction::Update()
{
    bool ret = false;
    switch (state) {

    case State::IDLE:
        ret = Idle();
        break;
    case State::NAVIGATION:
        ret = Navigation();

        break;

    default:
        break;
    }
    return ret;
}

bool Interaction::Idle()
{
    if(input->GetMouseButtonPressed(Qt::RightButton))
    {

        state = State::NAVIGATION;
    }
    else if(input->GetMouseButtonDown(Qt::LeftButton))
    {
        return true;
    }
    else {
        if(input->GetKeyDown(Qt::Key_F))
        {

        }
        if(input->GetKeyDown(Qt::Key_T))
        {

        }
        if(input->GetKeyDown(Qt::Key_R))
        {

        }
        if(input->GetKeyDown(Qt::Key_S))
        {

        }
    }
    return false;
}
bool Interaction::Navigation()
{
    if(!input->GetMouseButtonPressed(Qt::RightButton))
    {
        state = State::IDLE;
        return false;
    }

    bool cameraChange = false;
    float &yaw = mainCamera->yaw;
    float &pitch = mainCamera->pitch;

    int mouseXDelta = input->mouseX - input->mouseXPrev;
    int mouseYDelta = input->mouseYPrev -input->mouseY;

    printf( "input->mouseX %i \n",input->mouseX);
    printf( "input->mouseXPrev %i \n",input->mouseXPrev);
    printf( "input->mouseY %i \n",input->mouseY);
    printf( "input->mouseYPrev %i \n", input->mouseYPrev);
    if(mouseXDelta !=0||mouseYDelta!=0)
    {
        printf( "mouseXDelta %i \n",mouseXDelta);
        printf( "mouseYDelta %i \n",mouseYDelta);


        cameraChange = true;
        yaw -=0.3f*mouseXDelta;
        pitch -=0.3f*mouseYDelta;
        while(yaw <0.0f)
            yaw +=360.0f;
        while(yaw>360.0f)
            yaw-=360.0f;
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        QVector3D front(cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                        sinf(qDegreesToRadians(pitch)),
                        sin(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
        mainCamera->cameraFront = front.normalized();
    }
    QVector3D movement;

    if(input->GetKeyPressed(Qt::Key_W))
    {
        movement = +mainCamera->speed *mainCamera->cameraFront;

    }
    if(input->GetKeyPressed(Qt::Key_S))
    {
        movement = -mainCamera->speed * mainCamera->cameraFront;

    }
    if(input->GetKeyPressed(Qt::Key_A))
    {
        movement = -QVector3D::crossProduct( mainCamera->cameraFront, mainCamera->cameraUp)*mainCamera->speed;
        movement.normalize();
    }
    if(input->GetKeyPressed(Qt::Key_D))
    {
        movement = QVector3D::crossProduct( mainCamera->cameraFront, mainCamera->cameraUp)*mainCamera->speed;
        movement.normalize();
    }

    if(movement.length()!=0)
    {
        cameraChange = true;
        movement/=60.0f;
        mainCamera->position+=movement;
    }

    /*

       */

    return cameraChange;
}
