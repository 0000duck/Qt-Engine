#ifndef MESH_H
#define MESH_H

#include <QVector>

class VertexFormat;
class SubMesh;
struct aiNode;
struct aiScene;
struct aiMesh;

class Mesh
{
public:
    Mesh();
    //~Mesh() override;

    //Mesh* asMesh() override {return this;}

    void Update();
    void Destroy();

    void AddSubMesh(VertexFormat vFormat, void *data, int bytes);
    void AddSubMesh(VertexFormat vFormat, void *data, int bytes, unsigned int *indices, int bytes_indices);
    void LoadModel(const char *filename);

    QVector<SubMesh*> submeshes;

private:
    void ProcessNode(aiNode *node, const aiScene *scene);
    SubMesh* ProcessMesh(aiMesh *mesh, const aiScene *scene);
};

#endif // MESH_H
