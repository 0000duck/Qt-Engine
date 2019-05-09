#ifndef MESH_H
#define MESH_H

#include "Mesh/vertexformat.h"
#include "Mesh/submesh.h"
#include "QVector"

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
    void AddSubMesh(VertexFormat vertexFormat, void *data, int size,unsigned int *index, int indicesCount, const char* name, DrawType drawType = DrawType::TRIANGLES);

    void LoadModel(const char* fileName);
    void CreateCube();
    void CreateSphere();
    void CreatePlane();

    const QVector<SubMesh*> GetSubMeshes()const;
public:
    QVector<SubMesh*> subMeshes;

private:
    void ProcessNode(aiNode *node, const aiScene *scene);
    SubMesh* ProcessMesh(aiMesh *mesh, const aiScene* scene);
};

#endif // MESH_H
