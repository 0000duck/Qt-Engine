#include "interation.h"
#include "Scene/openglscene.h"
#include "Input/input.h"
#include "Render/camera.h"
#include "QtMath"
#include "GameObject/gameobject.h"
#include "Component/transform.h"
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

    if(scene->input->GetMouseButtonPressed(Qt::RightButton))
    {

        state = State::NAVIGATION;
    }
    else if(scene->input->GetMouseButtonDown(Qt::LeftButton))
    {
        QVector3D rayWorldspace = scene->camera->ScreenPointToWorldRay(scene->input->mouseX,scene->input->mouseY);
        printf("\n----------|\n");

        printf("rayWorldspace.x = %f \n",rayWorldspace.x());
        printf("rayWorldspace.y = %f \n",rayWorldspace.y());
        printf("rayWorldspace.z = %f \n",rayWorldspace.z());
        printf("----------|\n");
        return true;
    }
    else {
        int wheel = scene->input->mouseWheel;
        if(wheel!=0)
        {
            scene->camera->ProcessScrollMovement(wheel);
            cameraChange=true;

        }
        if(scene->input->GetKeyDown(Qt::Key_F))
        {
            if(scene->selected!=nullptr)
            {
                scene->camera->LookAt(scene->selected->GetTransform()->position);
                cameraChange=true;

            }
        }
        if(scene->input->GetKeyDown(Qt::Key_T))
        {

        }
        if(scene->input->GetKeyDown(Qt::Key_R))
        {

        }
        if(scene->input->GetKeyDown(Qt::Key_S))
        {

        }
    }
    return cameraChange;
}
bool Interaction::Navigation()
{
    if(!scene->input->GetMouseButtonPressed(Qt::RightButton))
    {
        state = State::IDLE;
        return false;
    }

    bool cameraChange = false;


    int mouseXDelta = scene->input->mouseXPrev - scene->input->mouseX;
    int mouseYDelta = scene->input->mouseYPrev - scene->input->mouseY;

    if(qAbs(mouseXDelta) > 1||qAbs(mouseYDelta) > 1)
    {
        scene->camera->ProcessMouseMovement(mouseXDelta,mouseYDelta,true);
        cameraChange = true;
    }

    QVector3D movement;

    if(scene->input->GetKeyPressed(Qt::Key_W))
    {
        scene->camera->ProcessKeyboard(CameraMovement::FORWARD,0.01);
        cameraChange=true;
    }
    if(scene->input->GetKeyPressed(Qt::Key_S))
    {
        scene->camera->ProcessKeyboard(CameraMovement::BACKWARD,0.01);
        cameraChange=true;

    }
    if(scene->input->GetKeyPressed(Qt::Key_A))
    {
        scene->camera->ProcessKeyboard(CameraMovement::LEFT,0.01);
        cameraChange=true;


    }
    if(scene->input->GetKeyPressed(Qt::Key_D))
    {
        scene->camera->ProcessKeyboard(CameraMovement::RIGHT,0.01);
        cameraChange=true;

    }
    return cameraChange;
}
bool Interaction::RayCast(const QVector3D &positionWorldSpace, const QVector3D & directionWorldSpace,GameObject** hit)
{
    /*
    foreach(GameObject go in scene.gameobjects)
        {
           MeshRenderer* meshRenderer = (MeshRenderer*)go.GetComponent(COMP_MESH_RENDERER);

           foreach(SubMesh* subMesh in meshRenderer->mesh->GetSubMeshes())
           {

           }
        }
        */
    return true;
}

