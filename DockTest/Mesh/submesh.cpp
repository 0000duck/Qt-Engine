#include "submesh.h"
#include "Scene/openglscene.h"
#include <stdio.h>
SubMesh::SubMesh(VertexFormat vertexFormat,void *data,int size)
{
    this->vertexFormat = vertexFormat;
    memcpy ( &this->data, &data,sizeof(data) );
    this->dataSize =size;
}
SubMesh::SubMesh(VertexFormat vertexFormat,void *data,int size,unsigned int *indice,int indicesCount)
{
    this->vertexFormat = vertexFormat;
    memcpy ( &this->data, &data,sizeof(data) );
    this->dataSize =size;
    memcpy ( & this->indice, &indice,sizeof(indice) );

    this->indicesCount =indicesCount;


}
SubMesh::~SubMesh()
{

}
void SubMesh::Update()
{
    printf("Update VAO Create");
    vao.create();
    printf("Update VAO Bind");
    vao.bind();

    printf("Update VBO Create");
    vbo.create();
    printf("Update VBO Bind");
    vbo.bind();
    printf("Update setUsagePattern");
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    printf("Update VBO Allocate");
    vbo.allocate(data,int(dataSize));
    printf("Update delete data");
    delete[] data;
    printf("Update data nullptr");
    data = nullptr;
    printf("Update indice !=nullptr");

    if(indice!=nullptr)
    {
        printf("Update IBO Create");
        ibo.create();
        printf("Update IBO Bind");
        ibo.bind();
        printf("Update setUsagePattern");
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        printf("Update allocate");
        ibo.allocate(indice,int(indicesCount* sizeof ( unsigned int)));
        printf("Update  delete[]indice");
        delete[]indice;
        printf("Update  indice = nullptr");
        indice = nullptr;
    }
    printf("Update  int location = 0; location < MAX_VERTEX_ATTRIBUTES;++location");
    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES;++location)
    {
        printf("Update VertexAttribute &attribute");
        VertexAttribute &attribute = vertexFormat.attribute[location];
        printf("Update attribute");

        if(attribute.enabled)
        {
            printf("Update glEnableVertexAttribArray");
            glFuncs->glEnableVertexAttribArray(GLuint(location));
            printf("Update glVertexAttribPointer");
            glFuncs->glVertexAttribPointer(GLuint(location),attribute.ncomp,GL_FLOAT,GL_FALSE,vertexFormat.size,(void*)(attribute.offset));
        }
    }
    printf("Update VAO RELEASE");
    vao.release();
    printf("Update VBO RELEASE");
    vbo.release();
    printf("Update IBO IsCreated");
    if(ibo.isCreated())
    {
        printf("Update IBO RELEASE");
        ibo.release();
    }
}
void SubMesh::Draw()
{
    int numVertices = dataSize/vertexFormat.size;
    vao.bind();
    if(indicesCount>0)
    {
        glFuncs->glDrawElements(GL_TRIANGLES,indicesCount,GL_UNSIGNED_INT,nullptr);

    }
    else {
        glFuncs->glDrawArrays(GL_TRIANGLES,0,numVertices);
    }
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
