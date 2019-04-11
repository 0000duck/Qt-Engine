#ifndef MESH_H
#define MESH_H
#include"Mesh/vertexformat.h"
#include "QVector"

class SubMesh;
struct aiNode;
struct aiMesh;
struct aiScene;
class Mesh
{
public:
    Mesh();
    void Draw();
    void Update();
    void Destroy();

    void AddSubMesh(VertexFormat vertexFormat, void *data, int size);
    void AddSubMesh(VertexFormat vertexFormat, void *data, int size,unsigned int *index, int indicesCount);

    void LoadModel(const char* fileName);
    void CreateCube();
    void CreateSphere();
    void CreatePlane();

public:
    QVector<SubMesh*> subMeshes;

private:
    void ProcessNode(aiNode *node, const aiScene *scene);
    SubMesh* ProcessMesh(aiMesh *mesh, const aiScene* scene);
};

#endif // MESH_H
