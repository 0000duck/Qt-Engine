#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#define MAX_VERTEX_ATTRIBUTES 10
struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:
    VertexFormat();
    void SetVertexAttribute(int location, int offset,int ncomp)
    {

    }
    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
};

#endif // VERTEXFORMAT_H
