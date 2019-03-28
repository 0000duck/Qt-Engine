#include "submesh.h"
#include "Scene/openglscene.h"

SubMesh::SubMesh(VertexFormat vertexFormat,void *data,int size)
{
    this->vertexFormat = vertexFormat;
    this->data = (unsigned char*) data;
    this->dataSize =size;
}
SubMesh::SubMesh(VertexFormat vertexFormat,void *data,int size,unsigned int *indice,int indicesCount)
{
    this->vertexFormat = vertexFormat;
    this->data = (unsigned char*) data;
    this->dataSize =size;
    this->indice = indice;
    this->indicesCount =indicesCount;

}
SubMesh::~SubMesh()
{

}
void SubMesh::Update()
{
    vao.create();
    vao.bind();


    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data,int(dataSize));
    delete[] data;
    data = nullptr;

    if(indice!=nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indice,int(indicesCount* sizeof ( unsigned int)));
        delete[]indice;
        indice = nullptr;
    }
    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES;++location)
    {
        VertexAttribute &attribute = vertexFormat.attribute[location];
        if(attribute.enabled)
        {
            glFuncs->glEnableVertexAttribArray(GLuint(location));
            glFuncs->glVertexAttribPointer(GLuint(location),attribute.ncomp,GL_FLOAT,GL_FALSE,vertexFormat.size,(void*)(attribute.offset));
        }
    }
    vao.release();
    vbo.release();
    if(ibo.isCreated())
        ibo.release();
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
