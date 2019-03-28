#include "Models/submesh.h"
#include "Models/vertexformat.h"
#include "Scene/openglscene.h"

SubMesh::SubMesh(VertexFormat vFormat, void *data, int size)
{
    vertexFormat = vFormat;
    this->data = (unsigned char*)data;
    this->dataSize = size;
}

SubMesh::SubMesh(VertexFormat vFormat, void *data, int size, unsigned int *indices, int indicesCount)
{
    vertexFormat = vFormat;
    this->data = (unsigned char*)data;
    this->dataSize = size;
    this->indices = indices;
    this->indicesCount = indicesCount;
}


void SubMesh::Update()
{
    // VAO: Vertex format description and state of VBOs
    vao.create();
    vao.bind();

    // VBO: Buffer with vertex data
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data, int(dataSize));
    delete[] data;
    data = nullptr;

    // IBO: Buffer with indexes
    if(indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indicesCount) * sizeof (unsigned int));
        delete[] indices;
        indices = nullptr;
    }

    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES; location++)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];
        if(attr.enabled)
        {
            glFuncs->glEnableVertexAttribArray(GLuint(location));
            glFuncs->glVertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT,GL_FALSE,
                                           vertexFormat.size,(void*)(attr.offset));
        }

        // Release
        vao.release();
        vbo.release();
        if(ibo.isCreated())
            ibo.release();
    }
}

void SubMesh::Draw()
{
    int numVertices = dataSize / vertexFormat.size;
    vao.bind();
    if(indicesCount>0)
        glFuncs->glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    else
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, numVertices);

    vao.release();
}

void SubMesh::Destroy()
{
   if(vbo.isCreated()) {vbo.destroy();}
   if(ibo.isCreated()) {ibo.destroy();}
   if(vao.isCreated()) {vao.destroy();}
}
