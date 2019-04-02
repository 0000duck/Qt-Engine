#ifndef SUBMESH_H
#define SUBMESH_H
#include "Mesh/vertexformat.h"
#include "QOpenGLBuffer"
#include "QOpenGLVertexArrayObject"
class SubMesh
{
public:
    SubMesh(VertexFormat vertexFormat,void *data,int size);
    SubMesh(VertexFormat vertexFormat,void *data,int size,unsigned int *indices,int indicesCount);
    ~SubMesh();


    void Update();
    void Draw();
    void Destroy();

private:
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
