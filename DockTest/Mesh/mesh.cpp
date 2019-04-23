#include "mesh.h"
#include "Mesh/submesh.h"
#include <qfile.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QVector3D>

#define H 32
#define V 16

static const float pi = 3.1416f;
struct Vertex
{
    QVector3D pos;
    QVector3D norm;
};

Mesh::Mesh()
{

}

void Mesh::Draw()
{
    foreach(SubMesh* subMesh, subMeshes)
    {
        subMesh->Draw();
    }
}

void Mesh::Update()
{
    foreach(SubMesh* subMesh, subMeshes)
    {
        subMesh->Update();
    }
}

void Mesh::Destroy()
{

}

void Mesh::AddSubMesh(VertexFormat vertexFormat, void *data, int size)
{
}

void Mesh::AddSubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *index, int indicesCount, DrawType drawType)
{
    printf("Create Submesh\n");
    SubMesh *subMesh = new SubMesh(vertexFormat, data, size, index, indicesCount, drawType);
    subMeshes.push_back(subMesh);
    printf("Created Submesh\n");
}

void Mesh::LoadModel(const char* fileName)
{
    Assimp::Importer import;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {

        return;
    }
    QByteArray data = file.readAll();

    const aiScene *scene = import.ReadFileFromMemory(data.data(),
                                                     data.size(),
                                                     aiProcess_Triangulate|
                                                     aiProcess_FlipUVs|
                                                     aiProcess_GenSmoothNormals|
                                                     aiProcess_OptimizeMeshes|
                                                     aiProcess_PreTransformVertices|
                                                     aiProcess_ImproveCacheLocality,
                                                     ".obj");

    if(!scene||scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode)
    {
        return;
    }

    ProcessNode(scene->mRootNode,scene);
    //needsUpdate = true;
}

void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i=0;i<node->mNumMeshes;++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        subMeshes.push_back(ProcessMesh(mesh,scene));
    }
    for(unsigned int i= 0; i < node->mNumChildren;++i)
    {
        ProcessNode(node->mChildren[i],scene);
    }
}

SubMesh* Mesh::ProcessMesh(aiMesh *mesh, const aiScene* scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;

    bool hasTexCoordenates = false;

    for(unsigned int i = 0; i < mesh->mNumVertices;++i)
    {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0])
        {
            hasTexCoordenates = true;
            vertices.push_back(mesh->mTextureCoords[0][i].z);
            vertices.push_back(mesh->mTextureCoords[0][i].z);
        }
    }

    for(unsigned int i=0;i<mesh->mNumFaces;++i)
    {
        aiFace face = mesh->mFaces[i];
        for(int j =0;j<face.mNumIndices;++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    VertexFormat vertexFormat;

    //Element 0 star on 0 size of 3
    vertexFormat.SetVertexAttribute(0,0,3);

    //Element 1 star on 3*size float size of 3
    vertexFormat.SetVertexAttribute(1,3*sizeof (float),3);

    if(hasTexCoordenates)
    {
        //Element 2 star on 6*size flost size of 2
        vertexFormat.SetVertexAttribute(2,6*sizeof (float),2);
    }

    return new SubMesh(vertexFormat,
                       &vertices[0],
                       vertices.size() * sizeof(float),
                       &indices[0],
                       indices.size());
}

void Mesh::CreateCube()
{
    printf("Create Sphere\n");

    // Vertices Creation
    Vertex cube[8];

    cube[0].pos = QVector3D(-1.0f, -1.0f, -1.0f);
    cube[1].pos = QVector3D( 1.0f, -1.0f, -1.0f);
    cube[2].pos = QVector3D(-1.0f,  1.0f, -1.0f);
    cube[3].pos = QVector3D( 1.0f,  1.0f, -1.0f);

    cube[4].pos = QVector3D(-1.0f, -1.0f, 1.0f);
    cube[5].pos = QVector3D( 1.0f, -1.0f, 1.0f);
    cube[6].pos = QVector3D(-1.0f,  1.0f, 1.0f);
    cube[7].pos = QVector3D( 1.0f,  1.0f, 1.0f);

    printf("Created Vertices\n");

    //Indices Creation
    unsigned int indices[36]=
    {
        // Front
        0,1,2,
        2,3,0,
        // Back
        6,5,4,
        4,7,6,
        // Left
        0,3,7,
        7,4,0,
        // Right
        1,5,6,
        6,2,1,
        // Up
        3,2,6,
        6,7,3,
        // Down
        5,1,0,
        0,4,5
    };


    VertexFormat vFormat;
    vFormat.SetVertexAttribute(0, 0, 3);
    vFormat.SetVertexAttribute(1, sizeof(QVector3D), 3);

    printf("Vertex Format\n");

    AddSubMesh(vFormat, cube, sizeof(cube), &indices[0], 36 * sizeof(unsigned int));

}

void Mesh::CreateSphere()
{
    printf("Create Sphere\n");

    // Vertices Creation
    Vertex sphere[H][V+1];
    for(int h = 0; h < H; h++)
    {
        for(int v = 0; v < V + 1; v++)
        {
            float nh = float(h) / H;
            float nv = float(v) / V - 0.5f;
            float angleH = 2 * pi *nh;
            float angleV = -pi * nv;
            sphere[h][v].pos.setX(sinf(angleH) * cos(angleV));
            sphere[h][v].pos.setY(-sinf(angleV));
            sphere[h][v].pos.setZ(cosf(angleH) * cosf(angleV));
            sphere[h][v].norm = sphere[h][v].pos;
        }
    }
    printf("Created Vertices\n");

    //Indices Creation
    unsigned int indices[H][V][6];
    for(unsigned int h = 0; h < H; h++)
    {
        for(unsigned int v = 0; v < V; v++)
        {
            indices[h][v][0] =  (h+0)    * (V+1) + v;
            indices[h][v][1] = ((h+1)%H) * (V+1) + v;
            indices[h][v][2] = ((h+1)%H) * (V+1) + v+1;
            indices[h][v][3] =  (h+0)    * (V+1) + v;
            indices[h][v][4] = ((h+1)%H) * (V+1) + v+1;
            indices[h][v][5] =  (h+0)    * (V+1) + v;
        }
    }
    printf("Created Indices\n");

    VertexFormat vFormat;
    vFormat.SetVertexAttribute(0, 0, 3);
    vFormat.SetVertexAttribute(1, sizeof(QVector3D), 3);

    printf("Vertex Format\n");

    AddSubMesh(vFormat, sphere, sizeof(sphere), &indices[0][0][0], H*V*6, DrawType::TRIANGLES_STRIP);
}

void Mesh::CreatePlane()
{

}
