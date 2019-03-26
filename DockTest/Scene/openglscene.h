#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

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

private:
    QImage GetScreenShot();  

public slots:
    void finalizeGL();
    void TakeScreenShot();

private :
    QImage image;
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    bool enableZtest = true;
    bool enableZwrite = true;
};

extern QOpenGLFunctions_3_3_Core* glFuncs;

#endif // OPENGLSCENE_H
