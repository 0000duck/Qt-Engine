#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QOpenGLWidget>


class OpenGLScene : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLScene(QWidget *parent = nullptr);

    // OpenGL function calls
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

signals:

public slots:
};

#endif // OPENGLSCENE_H
