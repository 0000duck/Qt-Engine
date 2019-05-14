#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>

class Scene;
class Mesh;
class ForwardRender;
class Camera;
class Input;
class Interaction;
class GameObject;
class DeferredRender;
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
    void Frame();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

public:
    bool needsUpdate = false;
    Camera* camera = nullptr;
    Input* input = nullptr;
    GameObject* selected = nullptr;

private :
    QTimer timer;

    Interaction* interaction = nullptr;

    ForwardRender* renderer = nullptr;
    //DeferredRender* renderer = nullptr;

    Scene* scene = nullptr;
    QImage image;
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    bool enableZtest = true;
    bool enableZwrite = true;
};

#endif // OPENGLSCENE_H
