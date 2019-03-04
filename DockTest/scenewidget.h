#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QObject>
#include <QWidget>

class SceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SceneWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:    

private:

    void paintEvent(QPaintEvent *event) override;
};

#endif // SCENEWIDGET_H
