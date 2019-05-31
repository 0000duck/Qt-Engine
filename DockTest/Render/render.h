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
    QOpenGLShaderProgram deferredProgram;
    QOpenGLShaderProgram blurProgram;
    QOpenGLShaderProgram glowProgram;

    QOpenGLShaderProgram quadProgram;



};

#endif // RENDER_H
