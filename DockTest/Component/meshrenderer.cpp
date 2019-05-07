#include "meshrenderer.h"
#include "Mesh/mesh.h"
#include "Mesh/submesh.h"
#include<QVector>

MeshRenderer::MeshRenderer(GameObject *myGO, Shape shape):Component(myGO, Type::COMP_MESH_RENDERER)
{
    mesh = new Mesh();
    this->shape = shape;

    // HANDLE PRIMITIVE CREATION
    switch(shape)
    {
    case Shape::CUBE:
    {
        mesh->CreateCube();
        break;
    }
    case Shape::SPHERE:
    {
        mesh->CreateSphere();
        break;
    }
    case Shape::PLANE:
    {
        mesh->CreatePlane();
        break;
    }
    case Shape::CUSTOM:
    {
        break;
    }
    default:
        break;
    }
}

Mesh* MeshRenderer::GetMesh()
{
    return mesh;
}

void MeshRenderer::Clear()
{
    mesh->Destroy();
}

void MeshRenderer::ChangeShape(const QString &meshName)
{
    if(meshName == "Cube")
    {
        mesh->CreateCube();
    }
    else if(meshName == "Plane")
    {
        mesh->CreatePlane();
    }
    else if(meshName == "Sphere")
    {
        mesh->CreateSphere();
    }
    else
    {
        mesh->LoadModel(meshName.toStdString().c_str());
    }
}

void MeshRenderer::Draw()
{
    mesh->Update();
    mesh->Draw();
}

