#include "interation.h"
#include "Input/input.h"
#include "Render/camera.h"
#include "QtMath"

#include "QTime"
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
    bool cameraChange = false;

    if(input->GetMouseButtonPressed(Qt::RightButton))
    {

        state = State::NAVIGATION;
    }
    else if(input->GetMouseButtonDown(Qt::LeftButton))
    {
        return true;
    }
    else {
        int wheel = input->mouseWheel;
        if(wheel!=0)
        {
            mainCamera->ProcessScrollMovement(wheel);
            cameraChange=true;

        }
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
    return cameraChange;
}
bool Interaction::Navigation()
{
    if(!input->GetMouseButtonPressed(Qt::RightButton))
    {
        state = State::IDLE;
        return false;
    }

    bool cameraChange = false;


    int mouseXDelta = input->mouseXPrev - input->mouseX;
    int mouseYDelta = input->mouseYPrev - input->mouseY;

    printf( "input->mouseX %i \n",input->mouseX);
    printf( "input->mouseXPrev %i \n",input->mouseXPrev);
    printf( "input->mouseY %i \n",input->mouseY);
    printf( "input->mouseYPrev %i \n", input->mouseYPrev);


    if(qAbs(mouseXDelta) > 1||qAbs(mouseYDelta) > 1)
    {
        mainCamera->ProcessMouseMovement(mouseXDelta,mouseYDelta,true);
        cameraChange = true;
    }

    QVector3D movement;

    if(input->GetKeyPressed(Qt::Key_W))
    {
        mainCamera->ProcessKeyboard(CameraMovement::FORWARD,0.01);
        cameraChange=true;
    }
    if(input->GetKeyPressed(Qt::Key_S))
    {
        mainCamera->ProcessKeyboard(CameraMovement::BACKWARD,0.01);
        cameraChange=true;

    }
    if(input->GetKeyPressed(Qt::Key_A))
    {
        mainCamera->ProcessKeyboard(CameraMovement::LEFT,0.01);
        cameraChange=true;


    }
    if(input->GetKeyPressed(Qt::Key_D))
    {
        mainCamera->ProcessKeyboard(CameraMovement::RIGHT,0.01);
        cameraChange=true;

    }






    return cameraChange;
}
