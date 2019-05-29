#include "mesh.h"
#include "Mesh/submesh.h"
#include "Scene/openglscene.h"

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
    foreach(SubMesh* subMesh, subMeshes)
    {
        subMesh->Destroy();
    }

    subMeshes.clear();
}

void Mesh::AddSubMesh(VertexFormat vertexFormat, void *data, int size)
{
}

void Mesh::AddSubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *index, int indicesCount, const char* name, DrawType drawType)
{
    printf("Create Submesh\n");
    SubMesh *subMesh = new SubMesh(vertexFormat, data, size, index, indicesCount, name, drawType);
    subMeshes.push_back(subMesh);
    printf("Created Submesh\n");
}

void Mesh::LoadModel(const char* fileName)
{
    Assimp::Importer import;    
    std::string path = "Models/";

    path += fileName;
    QFile file(path.c_str());
    if(!file.open(QIODevice::ReadOnly))
    {
        printf("returned\n");
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
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
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
                       indices.size(),
                       mesh->mName.C_Str());
}

void Mesh::CreateCube()
{
    printf("Create Cube\n");

    // Vertices Creation
    Vertex cube[24];

    // Front
    cube[0].pos = QVector3D(-1.0f, -1.0f, -1.0f); cube[0].norm = QVector3D(0.0f, 0.0f, -1.0f);
    cube[1].pos = QVector3D( 1.0f, -1.0f, -1.0f); cube[1].norm = QVector3D(0.0f, 0.0f, -1.0f);
    cube[2].pos = QVector3D( 1.0f,  1.0f, -1.0f); cube[2].norm = QVector3D(0.0f, 0.0f, -1.0f);
    cube[3].pos = QVector3D(-1.0f,  1.0f, -1.0f); cube[3].norm = QVector3D(0.0f, 0.0f, -1.0f);

    // Back
    cube[4].pos = QVector3D(-1.0f, -1.0f, 1.0f); cube[4].norm = QVector3D(0.0f, 0.0f, 1.0f);
    cube[5].pos = QVector3D( 1.0f, -1.0f, 1.0f); cube[5].norm = QVector3D(0.0f, 0.0f, 1.0f);
    cube[6].pos = QVector3D( 1.0f,  1.0f, 1.0f); cube[6].norm = QVector3D(0.0f, 0.0f, 1.0f);
    cube[7].pos = QVector3D(-1.0f,  1.0f, 1.0f); cube[7].norm = QVector3D(0.0f, 0.0f, 1.0f);

    // Right
    cube[8].pos =  QVector3D( 1.0f, -1.0f, -1.0f); cube[8].norm =  QVector3D(1.0f, 0.0f, 0.0f);
    cube[9].pos =  QVector3D( 1.0f, -1.0f,  1.0f); cube[9].norm =  QVector3D(1.0f, 0.0f, 0.0f);
    cube[10].pos = QVector3D( 1.0f,  1.0f,  1.0f); cube[10].norm = QVector3D(1.0f, 0.0f, 0.0f);
    cube[11].pos = QVector3D( 1.0f,  1.0f, -1.0f); cube[11].norm = QVector3D(1.0f, 0.0f, 0.0f);

    // Left
    cube[12].pos = QVector3D(-1.0f, -1.0f, -1.0f);  cube[12].norm = QVector3D(-1.0f, 0.0f, 0.0f);
    cube[13].pos = QVector3D(-1.0f, -1.0f,  1.0f);  cube[13].norm = QVector3D(-1.0f, 0.0f, 0.0f);
    cube[14].pos = QVector3D(-1.0f,  1.0f,  1.0f);  cube[14].norm = QVector3D(-1.0f, 0.0f, 0.0f);
    cube[15].pos = QVector3D(-1.0f,  1.0f, -1.0f);  cube[15].norm = QVector3D(-1.0f, 0.0f, 0.0f);

    // Top
    cube[16].pos = QVector3D(-1.0f,  1.0f, -1.0f);  cube[16].norm = QVector3D(0.0f,  1.0f, 0.0f);
    cube[17].pos = QVector3D( 1.0f,  1.0f, -1.0f);  cube[17].norm = QVector3D(0.0f,  1.0f, 0.0f);
    cube[18].pos = QVector3D( 1.0f,  1.0f,  1.0f);  cube[18].norm = QVector3D(0.0f,  1.0f, 0.0f);
    cube[19].pos = QVector3D(-1.0f,  1.0f,  1.0f);  cube[19].norm = QVector3D(0.0f,  1.0f, 0.0f);

    // Bottom
    cube[20].pos = QVector3D(-1.0f, -1.0f, -1.0f);  cube[20].norm = QVector3D(0.0f, -1.0f, 0.0f);
    cube[21].pos = QVector3D( 1.0f, -1.0f, -1.0f);  cube[21].norm = QVector3D(0.0f, -1.0f, 0.0f);
    cube[22].pos = QVector3D( 1.0f, -1.0f,  1.0f);  cube[22].norm = QVector3D(0.0f, -1.0f, 0.0f);
    cube[23].pos = QVector3D(-1.0f, -1.0f,  1.0f);  cube[23].norm = QVector3D(0.0f, -1.0f, 0.0f);

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
        12,15,14,
        14,13,12,
        // Right
        8,9,10,
        10,11,8,
        // Up
        16,17,18,
        18,19,16,
        // Down
        23,22,21,
        21,20,23
    };


    VertexFormat vFormat;
    vFormat.SetVertexAttribute(0, 0, 3);
    vFormat.SetVertexAttribute(1, sizeof(QVector3D), 3);

    printf("Vertex Format\n");

    AddSubMesh(vFormat, cube, sizeof(cube), &indices[0], 36 * sizeof(unsigned int), "Cube");

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

    AddSubMesh(vFormat, sphere, sizeof(sphere), &indices[0][0][0], H*V*6, "Sphere", DrawType::TRIANGLES_STRIP);
}

void Mesh::CreatePlane()
{
    printf("Create Cube\n");

    // Vertices Creation
    Vertex plane[4];

    // Front
    plane[0].pos = QVector3D(-3.0f,  0.0f, -3.0f);  plane[0].norm = QVector3D(0.0f,  1.0f, 0.0f);
    plane[1].pos = QVector3D( 3.0f,  0.0f, -3.0f);  plane[1].norm = QVector3D(0.0f,  1.0f, 0.0f);
    plane[2].pos = QVector3D( 3.0f,  0.0f,  3.0f);  plane[2].norm = QVector3D(0.0f,  1.0f, 0.0f);
    plane[3].pos = QVector3D(-3.0f,  0.0f,  3.0f);  plane[3].norm = QVector3D(0.0f,  1.0f, 0.0f);

    //Indices Creation
    unsigned int indices[6]
    {
        0,1,2,
        2,3,0
    };

    VertexFormat vFormat;
    vFormat.SetVertexAttribute(0, 0, 3);
    vFormat.SetVertexAttribute(1, sizeof(QVector3D), 3);

    printf("Vertex Format\n");

    AddSubMesh(vFormat, plane, sizeof(plane), &indices[0], 6 * sizeof(unsigned int), "Plane");
}
    const QVector<SubMesh*> Mesh::GetSubMeshes() const
    {
        return subMeshes;
    }
