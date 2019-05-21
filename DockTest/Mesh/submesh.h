#ifndef SUBMESH_H
#define SUBMESH_H

#include "Mesh/vertexformat.h"
#include "QOpenGLBuffer"
#include "QOpenGLVertexArrayObject"

class QOpenGLTexture;
class Material;
enum DrawType
{
    TRIANGLES,
    TRIANGLES_STRIP
};

class SubMesh
{
public:
    SubMesh(VertexFormat vertexFormat, void *data, int size);
    SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices, int indicesCount, const char* name, DrawType draw = DrawType::TRIANGLES);
    ~SubMesh();

    void Update();
    void Draw();
    void Destroy();
    const unsigned char* GetData()const;
    const unsigned int* GetIndice()const;

    void SetName(const char* name);
    Material* material = nullptr;
    QOpenGLTexture *texture = nullptr;

public:
    std::string textureName = "-";
    std::string meshName = "";

private:
    DrawType drawType;

    unsigned char *data = nullptr;
    size_t dataSize = 0;

    unsigned int *indice = nullptr;
    size_t indicesCount = 0;

    VertexFormat vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;
};

#endif // SUBMESH_H
