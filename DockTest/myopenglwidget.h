#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>

class MyOpenGlWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit MyOpenGlWidget(QWidget *parent = 0);
    ~MyOpenGlWidget();

    // From these methods we can call OpenGL functions
    void initializeGL() override;
    void resizeGL(int widht, int height) override;
    void paintGL() override;

signals:

public slots:
};

#endif // MYOPENGLWIDGET_H
