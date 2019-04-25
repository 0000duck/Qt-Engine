#include "meshrenderer.h"
#include "Mesh/mesh.h"

MeshRenderer::MeshRenderer(GameObject *myGO, Shape shape):Component(myGO, Type::COMP_MESH_RENDERER)
{
    mesh = new Mesh();

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

