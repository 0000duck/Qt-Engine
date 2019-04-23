#include "submesh.h"
#include "Scene/openglscene.h"
#include <stdio.h>

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size) : ibo(QOpenGLBuffer::IndexBuffer)
{
    this->vertexFormat = vertexFormat;
    memcpy(this->data, data, size);
    this->dataSize = size;
}

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices,int indicesCount, DrawType drawType):
    ibo(QOpenGLBuffer::IndexBuffer),
    drawType(drawType)
{
    printf("Submesh Constructor\n");

    this->vertexFormat = vertexFormat;
    this->data = new unsigned char[size];
    memcpy(this->data, data, size);
    this->dataSize = size;
    printf("Data\n");

    int sizeIndice = indicesCount * sizeof(unsigned int);
    this->indice = new unsigned int[sizeIndice];
    memcpy(this->indice, indices, sizeIndice);
    this->indicesCount = indicesCount;
    printf("Indices\n");

}

SubMesh::~SubMesh()
{

}

void SubMesh::Update()
{
    printf("VAO Create \n");
    vao.create();
    vao.bind();

    printf("VBO Create \n");
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data,int(dataSize));
    delete[] data;
    data = nullptr;
    if(indice!=nullptr)
    {
        printf("Update IBO Create \n");
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indice,int(indicesCount* sizeof ( unsigned int)));
        delete[]indice;
        indice = nullptr;
    }
    printf("Update VertexAttribute \n");

    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES;++location)
    {
        VertexAttribute &attribute = vertexFormat.attribute[location];

        if(attribute.enabled)
        {
            printf("Update glEnableVertexAttribArray\n");
            glFuncs->glEnableVertexAttribArray(GLuint(location));
            printf("Update glVertexAttribPointer\n");
            glFuncs->glVertexAttribPointer(GLuint(location),attribute.ncomp,GL_FLOAT,GL_FALSE,vertexFormat.size,(void*)(attribute.offset));
        }
    }
    printf("VAO RELEASE \n");
    vao.release();
    printf("VBO RELEASE \n");
    vbo.release();

    if(ibo.isCreated())
    {
        printf("IBO RELEASE \n");
        ibo.release();
    }
}

void SubMesh::Draw()
{
    int numVertices = dataSize/vertexFormat.size;
    vao.bind();

    if (indicesCount > 0)
    {
        switch(drawType)
        {
            case DrawType::TRIANGLES:
            glFuncs->glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
            break;

            case DrawType::TRIANGLES_STRIP:
            glFuncs->glDrawElements(GL_TRIANGLE_STRIP, indicesCount, GL_UNSIGNED_INT, nullptr);
            break;
        }
    }
    else
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, numVertices);

    vao.release();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated())
        vbo.destroy();
    if(ibo.isCreated())
        vbo.destroy();
    if(vao.isCreated())
        vbo.destroy();
}
