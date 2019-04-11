#ifndef RENDER_H
#define RENDER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Camera;
class Mesh;
class Renderer
{
public:
    Renderer();
    virtual ~Renderer();
    virtual void Render(Camera* camera);

public:
    Mesh* mesh = nullptr;

protected:
    QOpenGLShaderProgram program;


};

#endif // RENDER_H
