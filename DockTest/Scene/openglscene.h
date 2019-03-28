#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
class Scene;
class Mesh;
extern QOpenGLFunctions_3_3_Core *glFuncs;

class OpenGLScene : public QOpenGLWidget,
                    protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit OpenGLScene(QWidget *parent = nullptr);
    ~OpenGLScene() override;

    // OpenGL function calls
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    bool GetScene(Scene *scene);
private:
    QImage GetScreenShot();  

public slots:
    void finalizeGL();
    void TakeScreenShot();


private :
    Scene* scene = nullptr;
    Mesh* mesh = nullptr;
    QImage image;
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    bool enableZtest = true;
    bool enableZwrite = true;
};

#endif // OPENGLSCENE_H
