#include "forwardrender.h"
#include "camera.h"
#include "Scene/openglscene.h"
#include "Scene/scene.h"
#include "Mesh/mesh.h"
#include "GameObject/gameobject.h"
#include "Component/transform.h"
#include "Component/meshrenderer.h"
#include <QVector3D>

ForwardRender::ForwardRender()
{
}

ForwardRender::~ForwardRender()
{

}
void ForwardRender::InitProgram()
{
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/cameraShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/cameraShader_tex.frag");
    program.link();
    program.bind();


    //mesh->Update();
    program.release();

}

void ForwardRender::Render(Camera *camera, Scene* scene)
{
    if(program.bind())
    {
        if(scene!= nullptr)
        {
            foreach(GameObject* go, scene->gameObjects)
            {

                QMatrix4x4 model;
                model.setToIdentity();

                Transform* transform = (Transform*)go->GetComponent(Type::COMP_TRANSFORM);
                model.translate(transform->position.x(), transform->position.y(),transform->position.z());
                model.rotate(transform->quatRotation);
                model.scale(transform->scale.x(), transform->scale.y(),transform->scale.z());

                QMatrix4x4 modelView;
                modelView = camera->viewMatrix * model;
                GLuint mvMatrix = program.uniformLocation("modelViewMat");

                glFuncs->glUniformMatrix4fv(mvMatrix, 1, GL_FALSE, modelView.data());

                GLuint pMatrix = program.uniformLocation("projectionMat");

                glFuncs->glUniformMatrix4fv(pMatrix, 1, GL_FALSE, camera->projectionMatrix.data());


                ((MeshRenderer*)go->GetComponent(Type::COMP_MESH_RENDERER))->Draw();
                //printf("Draw");

            }
        }
    }

    program.release();

}
