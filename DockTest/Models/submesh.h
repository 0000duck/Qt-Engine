#ifndef SUBMESH_H
#define SUBMESH_H

#include"Models/vertexformat.h"
#include<QOpenGLBuffer>
#include<QOpenGLVertexArrayObject>


class SubMesh
{
public:
    SubMesh(VertexFormat vFormat, void *data, int size);
    SubMesh(VertexFormat vFormat, void *data, int size, unsigned int *indices, int indicesCount);

    void Update();
    void Draw();
    void Destroy();

private:
    unsigned char *data = nullptr;
    size_t dataSize = 0;

    unsigned int *indices = nullptr;
    size_t indicesCount = 0;

    VertexFormat vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;


};

#endif // SUBMESH_H
