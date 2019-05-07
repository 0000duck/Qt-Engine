#ifndef SUBMESH_H
#define SUBMESH_H
#include "Mesh/vertexformat.h"
#include "QOpenGLBuffer"
#include "QOpenGLVertexArrayObject"

enum DrawType
{
    TRIANGLES,
    TRIANGLES_STRIP
};

class SubMesh
{
public:
    SubMesh(VertexFormat vertexFormat, void *data, int size);
    SubMesh(VertexFormat vertexFormat, void *data, int size,unsigned int *indices, int indicesCount, DrawType draw = DrawType::TRIANGLES);
    ~SubMesh();

    void Update();
    void Draw();
    void Destroy();
    const unsigned char* GetData()const;
    const unsigned int* GetIndice()const;

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
