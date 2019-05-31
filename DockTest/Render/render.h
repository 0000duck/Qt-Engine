#ifndef RENDER_H
#define RENDER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Camera;
class Mesh;
class GameObject;
class Scene;

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();
    virtual void Render(Camera* camera, Scene* scene);

public:

protected:
    QOpenGLShaderProgram program;
    QOpenGLShaderProgram screenProgram;
    QOpenGLShaderProgram quadProgram;
    QOpenGLShaderProgram blurProgram;


};

#endif // RENDER_H
