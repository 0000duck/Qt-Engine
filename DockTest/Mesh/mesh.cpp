#include "mesh.h"
#include "Mesh/submesh.h"
#include <qfile.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
void Mesh::AddSubMesh(VertexFormat vertexFormat,void *data,int size)
{

}
void Mesh::AddSubMesh(VertexFormat vertexFormat,void *data,int size,unsigned int *index,int indicesCount)
{

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
    //Element 1 star on 3*size flost size of 3

    vertexFormat.SetVertexAttribute(1,3*sizeof (float),3);

    if(hasTexCoordenates)
    {
        //Element 2 star on 6*size flost size of 2
        vertexFormat.SetVertexAttribute(2,6*sizeof (float),2);
    }

    return new SubMesh(vertexFormat,
                       &vertices[0],
                       vertices.size(),
                       &indices[0],
                       indices.size());
}
